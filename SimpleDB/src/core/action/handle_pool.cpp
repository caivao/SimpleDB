//
//  handle_pool.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "handle_pool.hpp"
#include <thread>
#include <unordered_map>

namespace SDB {
    
    std::unordered_map<std::string, std::pair<std::shared_ptr<HandlePool>, int>> HandlePool::_pools;
    std::mutex HandlePool::_mutex;
    const int HandlePool::_hardware_concurrency = std::thread::hardware_concurrency();
    const int HandlePool::_max_concurrency = 64;
    
    HandlePoolReleasable HandlePool::get_pool(const std::string &path, const Configure &configure)
    {
        std::shared_ptr<HandlePool> pool = nullptr;
        std::lock_guard<std::mutex> lock_guard(_mutex);
        auto iter = _pools.find(path);
        if (iter == _pools.end()) {
            pool.reset(new HandlePool(path, configure));
            _pools.insert({path, {pool, 1}});
        } else {
            pool = iter->second.first;
            ++iter->second.second;
        }
        //Can I store iter of unordered_map for later use?
        return HandlePoolReleasable(pool, [](std::shared_ptr<HandlePool> &pool) {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            const auto &iter = _pools.find(pool->path);
            if (--iter->second.second == 0) {
                _pools.erase(iter);
            }
        });
    }
    
    void HandlePool::purge_all_free_handles()
    {
        std::list<std::shared_ptr<HandlePool>> pools;
        {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            for (const auto &iter : _pools) {
                pools.push_back(iter.second.first);
            }
        }
        for (const auto &handlePool : pools) {
            handlePool->purge_free_handles();
        }
    }
    
    HandlePool::HandlePool(const std::string &path, const Configure &configure)
    : path(path)
    , _configure(configure)
    , _handles(_hardware_concurrency)
    , _alive_handle_count(0)
    {}
    
    void HandlePool::blockade()
    {
        _rwlock.lock_write();
    }
    
    void HandlePool::unblockade()
    {
        _rwlock.unlock_write();
    }
    
    bool HandlePool::is_blockaded() const
    {
        return _rwlock.is_writing();
    }
    
    void HandlePool::drain(HandlePool::OnDrained on_drained)
    {
        _rwlock.lock_write();
        int size = (int) _handles.clear();
        _alive_handle_count -= size;
        if (on_drained) {
            on_drained();
        }
        _rwlock.unlock_write();
    }
    
    void HandlePool::purge_free_handles()
    {
        _rwlock.lock_read();
        int size = (int) _handles.clear();
        _alive_handle_count -= size;
        _rwlock.unlock_read();
    }
    
    bool HandlePool::is_drained()
    {
        return _alive_handle_count == 0;
    }
    
    HandleReleasable HandlePool::flow_out(Error &error)
    {
        _rwlock.lock_read();
        std::shared_ptr<HandleWrapper> handle_wrapper = _handles.popBack();
        if (handle_wrapper == nullptr) {
            if (_alive_handle_count < _max_concurrency) {
                handle_wrapper = generate(error);
                if (handle_wrapper) {
                    ++_alive_handle_count;
                    if (_alive_handle_count > _hardware_concurrency) {
                        Error::report(("The concurrency of database with "+ std::to_string(_alive_handle_count) + " exceeds the concurrency of hardware:" + std::to_string(_hardware_concurrency)).c_str(), 0, nullptr);
                    }
                }
            } else {
                Error::report("The concurrency of database exceeds the max concurrency", -1, &error);
            }
        }
        if (handle_wrapper) {
            if (invoke(handle_wrapper, error)) {
                return HandleReleasable(handle_wrapper,
                                        [this](std::shared_ptr<HandleWrapper> &handle_wrapper) {
                                            flow_back(handle_wrapper);
                                        });
            }
        }
        
        handle_wrapper = nullptr;
        _rwlock.unlock_read();
        return HandleReleasable(nullptr, nullptr);
    }
    
    void HandlePool::flow_back(const std::shared_ptr<HandleWrapper> &handle_wrapper)
    {
        if (handle_wrapper) {
            bool inserted = _handles.push_back(handle_wrapper);
            _rwlock.unlock_read();
            if (!inserted) {
                --_alive_handle_count;
            }
        }
    }
    
    std::shared_ptr<HandleWrapper> HandlePool::generate(Error &error)
    {
        std::shared_ptr<Handle> handle(new Handle(path));
        Configure configure = _configure; //cache config to avoid multi-thread assigning
        if (!handle->open()) {
            error = handle->get_error();
            return nullptr;
        }
        if (configure.invoke(handle, error)) {
            return std::shared_ptr<HandleWrapper>(new HandleWrapper(handle, configure));
        }
        return nullptr;
    }
    
    bool HandlePool::fill_one(Error &error)
    {
        _rwlock.lock_read();
        std::shared_ptr<HandleWrapper> handle_wrapper = generate(error);
        bool result = false;
        if (handle_wrapper) {
            result = true;
            bool inserted = _handles.push_back(handle_wrapper);
            if (inserted) {
                ++_alive_handle_count;
            }
        }
        _rwlock.unlock_read();
        return result;
    }
    
    bool HandlePool::invoke(std::shared_ptr<HandleWrapper> &handle_wrapper, Error &error)
    {
        Configure new_configure = _configure; //cache config to avoid multi-thread assigning
        if (new_configure != handle_wrapper->configure) {
            if (!new_configure.invoke(handle_wrapper->handle, error)) {
                return false;
            }
            handle_wrapper->configure = new_configure;
        }
        error.reset();
        return true;
    }
    
    void HandlePool::set_config(const std::string &name, const Config &config, Configure::Order order)
    {
        _configure.set_config(name, config, order);
    }
    
    void HandlePool::set_config(const std::string &name, const Config &config)
    {
        _configure.set_config(name, config);
    }
    
}

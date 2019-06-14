//
//  handle_pool.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
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
        std::lock_guard<std::mutex> lockGuard(_mutex);
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
            std::lock_guard<std::mutex> lockGuard(_mutex);
            const auto &iter = _pools.find(pool->path);
            if (--iter->second.second == 0) {
                _pools.erase(iter);
            }
        });
    }
    
    void HandlePool::PurgeFreeHandlesInAllPool()
    {
        std::list<std::shared_ptr<HandlePool>> handlePools;
        {
            std::lock_guard<std::mutex> lockGuard(_mutex);
            for (const auto &iter : _pools) {
                handlePools.push_back(iter.second.first);
            }
        }
        for (const auto &handlePool : handlePools) {
            handlePool->purgeFreeHandles();
        }
    }
    
    HandlePool::HandlePool(const std::string &thePath, const Configure &configure)
    : path(thePath)
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
    
    bool HandlePool::isBlockaded() const
    {
        return _rwlock.is_writing();
    }
    
    void HandlePool::drain(HandlePool::OnDrained onDrained)
    {
        _rwlock.lock_write();
        int size = (int) _handles.clear();
        _alive_handle_count -= size;
        if (onDrained) {
            onDrained();
        }
        _rwlock.unlock_write();
    }
    
    void HandlePool::purgeFreeHandles()
    {
        _rwlock.lock_read();
        int size = (int) _handles.clear();
        _alive_handle_count -= size;
        _rwlock.unlock_read();
    }
    
    bool HandlePool::isDrained()
    {
        return _alive_handle_count == 0;
    }
    
    HandleReleasable HandlePool::flowOut(Error &error)
    {
        _rwlock.lock_read();
        std::shared_ptr<HandleWrapper> handle_wrapper = _handles.popBack();
        if (handle_wrapper == nullptr) {
            if (_alive_handle_count < _max_concurrency) {
                handle_wrapper = generate(error);
                if (handle_wrapper) {
                    ++_alive_handle_count;
                    if (_alive_handle_count > _hardware_concurrency) {
                        //                        WCDB::Error::Warning(
                        //                                             ("The concurrency of database:" +
                        //                                              std::to_string(tag.load()) + " with " +
                        //                                              std::to_string(_aliveHandleCount) +
                        //                                              " exceeds the concurrency of hardware:" +
                        //                                              std::to_string(_hardwareConcurrency)).c_str());
                    }
                }
            } else {
                //                Error::ReportCore(
                //                                  tag.load(), path, Error::CoreOperation::FlowOut,
                //                                  Error::CoreCode::Exceed,
                //                                  "The concurrency of database exceeds the max concurrency",
                //                                  &error);
            }
        }
        if (handle_wrapper) {
            if (invoke(handle_wrapper, error)) {
                return HandleReleasable(handle_wrapper,
                                        [this](std::shared_ptr<HandleWrapper> &handle_wrapper) {
                                            flowBack(handle_wrapper);
                                        });
            }
        }
        
        handle_wrapper = nullptr;
        _rwlock.unlock_read();
        return HandleReleasable(nullptr, nullptr);
    }
    
    void HandlePool::flowBack(const std::shared_ptr<HandleWrapper> &handle_wrapper)
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

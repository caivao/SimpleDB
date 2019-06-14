//
//  handle_pool.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef handle_pool_hpp
#define handle_pool_hpp

#include "declare.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include "configure.hpp"
#include "handle_releasable.hpp"
#include "statement_releasable.hpp"
#include <unordered_map>

namespace SDB {
    
    class HandlePool;
    typedef Releasable<std::shared_ptr<HandlePool>> HandlePoolReleasable;
    
    class HandlePool {
    public:
        static HandlePoolReleasable get_pool(const std::string &path, const Configure &configure);
        static void purge_all_free_handles();
        
        const std::string path;
        
        HandleReleasable flow_out(Error &error);
        bool fill_one(Error &error);
        
        bool is_drained();
        typedef std::function<void(void)> OnDrained;
        void blockade();
        void drain(HandlePool::OnDrained on_drained);
        void unblockade();
        bool is_blockaded() const;
        
        void purge_free_handles();
        
        void set_config(const std::string &name, const Config &config, Configure::Order order);
        void set_config(const std::string &name, const Config &config);
        
    protected:
        HandlePool(const std::string &path, const Configure &configure);
        HandlePool(const HandlePool &) = delete;
        HandlePool &operator=(const HandlePool &) = delete;
        
        bool invoke(std::shared_ptr<HandleWrapper> &handle_wrapper, Error &error);
        
        void flow_back(const std::shared_ptr<HandleWrapper> &handle_wrapper);
        
        ConcurrentList<HandleWrapper> _handles;
        std::atomic<int> _alive_handle_count;
        static const int _hardware_concurrency;
        static const int _max_concurrency;
        
        static std::unordered_map<std::string, std::pair<std::shared_ptr<HandlePool>, int>> _pools; //path->{pool, reference}
        static std::mutex _mutex;
        Configure _configure;
        RWlock _rwlock;
        std::shared_ptr<HandleWrapper> generate(Error &error);
    };
}

#endif /* handle_pool_hpp */

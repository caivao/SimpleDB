//
//  handle_pool.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
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
        static void PurgeFreeHandlesInAllPool();
        
    protected:
        static std::unordered_map<std::string, std::pair<std::shared_ptr<HandlePool>, int>> _pools; //path->{pool, reference}
        static std::mutex _mutex;
        
    public:
        const std::string path;
        
        HandleReleasable flowOut(Error &error);
        bool fill_one(Error &error);
        
        bool isDrained();
        typedef std::function<void(void)> OnDrained;
        void blockade();
        void drain(HandlePool::OnDrained onDrained);
        void unblockade();
        bool isBlockaded() const;
        
        void purgeFreeHandles();
        
        void set_config(const std::string &name, const Config &config, Configure::Order order);
        void set_config(const std::string &name, const Config &config);
        
    protected:
        HandlePool(const std::string &path, const Configure &configs);
        HandlePool(const HandlePool &) = delete;
        HandlePool &operator=(const HandlePool &) = delete;
        
        std::shared_ptr<HandleWrapper> generate(Error &error);
        
        bool invoke(std::shared_ptr<HandleWrapper> &handleWrap, Error &error);
        
        Configure _configure;
        RWlock _rwlock;
        
        void flowBack(const std::shared_ptr<HandleWrapper> &handleWrap);
        
        ConcurrentList<HandleWrapper> _handles;
        std::atomic<int> _alive_handle_count;
        static const int _hardware_concurrency;
        static const int _max_concurrency;
    };
}

#endif /* handle_pool_hpp */

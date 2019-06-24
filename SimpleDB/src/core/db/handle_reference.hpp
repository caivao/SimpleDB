//
//  handle_reference.hpp
//  SimpleDB
//
//  Created by OYOL on 2019/6/24.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef handle_reference_hpp
#define handle_reference_hpp

#include "declare.hpp"
#include "configure.hpp"
#include "handle.hpp"
#include "recycle.hpp"
#include <unordered_map>
#include <mutex>

namespace SDB {
    
    struct HandleRefWrapper {
        HandleRefWrapper(const std::shared_ptr<Handle> &handle, const ConfigList configs)
        : handle(handle), configs(configs)
        {}
        
        std::shared_ptr<Handle> handle;
        ConfigList configs;
    };
    
    class HandleRef {
        
    protected:
        static std::unordered_map<std::string, std::pair<std::shared_ptr<HandleRef>, int>> _pool;
        static std::mutex _mutex;
        
        std::shared_ptr<HandleRefWrapper> _value;
        
    public:
        
        
    };
}

#endif /* handle_reference_hpp */

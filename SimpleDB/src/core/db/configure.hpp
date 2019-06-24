//
//  configure.hpp
//  SimpleDB
//
//  Created by OYOL on 2019/6/21.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef configure_hpp
#define configure_hpp

#include "declare.hpp"

namespace SDB {
    
    typedef std::function<bool(std::shared_ptr<Handle> &, Error &)> Config;
    typedef struct ConfigWrapper ConfigWrapper;
    
    class ConfigList {
    public:
        void push(const std::string &name, const Config &config, int priority);
        void push(const std::string &name, const Config &config);
        
        bool invoke(std::shared_ptr<Handle> &handle, Error &error);
        
        ConfigList(void);
        ConfigList(std::initializer_list<const ConfigWrapper> configs);
        
        Config config(const std::string &name) const;
    protected:
        typedef std::list<ConfigWrapper> ConfigWapperSource;
        std::shared_ptr<ConfigWapperSource> _configs;
        
    };
    
    struct ConfigWrapper {
        const std::string name;
        const Config invoke;
        const int priority;
        
        ConfigWrapper(const std::string &name, const Config &config, const int priority)
        : name(name), invoke(config), priority(priority)
        {}
        
    };
}

#endif /* configure_hpp */

//
//  configure.cpp
//  SimpleDB
//
//  Created by OYOL on 2019/6/21.
//  Copyright © 2019 feng. All rights reserved.
//

#include "configure.hpp"

namespace SDB {
    
    ConfigList::ConfigList(void)
    : _configs(new ConfigWapperSource)
    {}
    
    ConfigList::ConfigList(std::initializer_list<const ConfigWrapper> configs)
    : _configs(new ConfigWapperSource)
    {
        for(auto const &c : configs) {
            _configs->push_back(c);
        }
    }
    
    void ConfigList::push(const std::string &name, const Config &config, int priority)
    {
        std::shared_ptr<ConfigWapperSource> current = _configs;
        std::shared_ptr<ConfigWapperSource> next(new ConfigWapperSource);
        
        bool inserted = false;
        
        for (auto const &c : *current.get()) {
            if(SDBunlikely(!inserted && priority < c.priority)) {
                next->push_back({name, config, priority});
                inserted = true;
            } else if(name != c.name){
                next->push_back(c);
            }
        }
        
        if(!inserted) {
            next->push_back({name, config, priority});
        }
        _configs = next;
    }
    
    void ConfigList::push(const std::string &name, const Config &config)
    {
        std::shared_ptr<ConfigWapperSource> current = _configs;
        std::shared_ptr<ConfigWapperSource> next(new ConfigWapperSource);
        
        bool inserted = false;
        
        for (auto const &c : *current.get()) {
            if(name != c.name){
                next->push_back(c);
            } else {
                next->push_back({name, config, c.priority});
                inserted = true;
            }
        }
        
        if(!inserted) {
            next->push_back({name, config, INT32_MAX});
        }
        _configs = next;
    }
    
    bool ConfigList::invoke(std::shared_ptr<Handle> &handle, Error &error)
    {
        std::shared_ptr<ConfigWapperSource> current = _configs;
        
        for (auto const &c : *current.get()) {
            if(c.invoke && !c.invoke(handle, error)) {
                return false;
            }
        }
        return true;
    }
    
    Config ConfigList::config(const std::string &name) const
    {
        std::shared_ptr<ConfigWapperSource> current = _configs;
        for (auto const &c : *current.get()) {
            if(c.name == name) {
                return c.invoke;
            }
        }
        return nullptr;
    }
}

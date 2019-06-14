//
//  configure.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "configure.hpp"

namespace SDB {
    
    Configure::Configure()
    : _configures(new ConfigureList)
    {
    }
    
    Configure::Configure(std::initializer_list<const ConfigWrapper> configures)
    : _configures(new ConfigureList)
    {
        for (const auto &c : configures) {
            _configures->push_back(c);
        }
    }
    
    void Configure::set_config(const std::string &name, const Config &config, Configure::Order order)
    {
        std::shared_ptr<ConfigureList> configures = _configures;
        std::shared_ptr<ConfigureList> new_configures(new ConfigureList);
        bool inserted = false;
        for (const auto &wrapper : *configures.get()) {
            if (!inserted && order < wrapper.order) {
                new_configures->push_back({name, config, order});
                inserted = true;
            } else if (name != wrapper.name) {
                new_configures->push_back(wrapper);
            }
        }
        if (!inserted) {
            new_configures->push_back({name, config, order});
        }
        _configures = new_configures;
    }
    
    void Configure::set_config(const std::string &name, const Config &config)
    {
        std::shared_ptr<ConfigureList> configures = _configures;
        std::shared_ptr<ConfigureList> new_configures(new ConfigureList);
        bool inserted = false;
        for (const auto &wrapper : *configures.get()) {
            if (name != wrapper.name) {
                new_configures->push_back(wrapper);
            } else {
                new_configures->push_back({name, config, wrapper.order});
                inserted = true;
            }
        }
        if (!inserted) {
            new_configures->push_back({name, config, INT_MAX});
        }
        _configures = new_configures;
    }
    
    bool Configure::invoke(std::shared_ptr<Handle> &handle, Error &error)
    {
        std::shared_ptr<ConfigureList> configures = _configures;
        for (const auto &configure : *configures.get()) {
            if (configure.invoke && !configure.invoke(handle, error)) {
                return false;
            }
        }
        return true;
    }
    
    Config Configure::get_config(const std::string &name) const
    {
        std::shared_ptr<ConfigureList> configures = _configures;
        for (const auto &configure : *configures.get()) {
            if (configure.name == name) {
                return configure.invoke;
            }
        }
        return nullptr;
    }
    
    bool operator==(const Configure &lhs, const Configure &rhs)
    {
        return lhs._configures == rhs._configures;
    }
    
    bool operator!=(const Configure &lhs, const Configure &rhs)
    {
        return lhs._configures != rhs._configures;
    }
    
}

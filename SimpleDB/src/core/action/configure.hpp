//
//  configure.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef configure_hpp
#define configure_hpp

#include "declare.hpp"
#include <functional>
#include <list>
#include <memory>
#include <limits.h>

namespace SDB {
    
    typedef std::function<bool(std::shared_ptr<Handle> &, Error &)> Config;
    typedef struct ConfigWrapper ConfigWraper;
    
    class Configure {
    public:
        typedef int Order; //Small numbers in front
        void set_config(const std::string &name, const Config &config, Configure::Order order);
        void set_config(const std::string &name, const Config &config);
        
        bool invoke(std::shared_ptr<Handle> &handle, Error &error);
        
        friend bool operator==(const Configure &lhs, const Configure &rhs);
        friend bool operator!=(const Configure &lhs, const Configure &rhs);
        
        Configure(void);
        Configure(std::initializer_list<const ConfigWrapper> configures);
        
        Config get_config(const std::string &name) const;
        
    protected:
        typedef std::list<ConfigWrapper> ConfigureList;
        
        std::shared_ptr<ConfigureList> _configures;
    };
    
    struct ConfigWrapper {
        const std::string name;
        const Config invoke;
        const Configure::Order order;
        ConfigWrapper(const std::string &name, const Config &config, Configure::Order order)
        : name(name), invoke(config), order(order)
        {}
    };
}

#endif /* configure_hpp */

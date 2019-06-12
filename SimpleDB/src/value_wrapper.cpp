//
//  value_wrapper.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "value_wrapper.hpp"

namespace SDB {
    
    ValueWrapper::ValueWrapper(const char *value)
    : Describable(value ? stringValue(value) : "")
    {}
    
    ValueWrapper::ValueWrapper(const std::string &value)
    : Describable(stringValue(value))
    {}
    
    ValueWrapper::ValueWrapper(const std::nullptr_t &value)
    : Describable("NULL")
    {}
    
    ValueWrapper::ValueWrapper(const void *value, int size)
    : Describable(stringValue(std::string((const char *) value, size)))
    {}
    
    std::string ValueWrapper::stringValue(const std::string &value)
    {
        return "'" + value + "'";
    }
}

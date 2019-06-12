//
//  value_wrapper.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef value_wrapper_hpp
#define value_wrapper_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    class ValueWrapper : public Describable {
    public:
        template <typename T>
        ValueWrapper(const T &value,
                     typename std::enable_if<std::is_arithmetic<T>::value ||
                     std::is_enum<T>::value>::type * = nullptr)
        : Describable(std::to_string(value))
        {}
        
        ValueWrapper(const char *value);
        ValueWrapper(const std::string &value);
        ValueWrapper(const std::nullptr_t &value);
        ValueWrapper(const void *value, int size);
    protected:
        static std::string stringValue(const std::string &value);
    };
}

#endif /* value_wrapper_hpp */

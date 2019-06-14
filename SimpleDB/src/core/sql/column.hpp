//
//  column.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef column_hpp
#define column_hpp

#include "declare.hpp"
#include "describable.hpp"
#include "value_wrapper.hpp"

namespace SDB {
    class Column : public Describable {
        
    public:
        static const Column all;
        static const Column rowid;
        
        Column(void);
        Column(const char *name);
        Column(const std::string &name);
        template <typename T>
        Column(const T &value,
             typename std::enable_if<std::is_arithmetic<T>::value ||
             std::is_enum<T>::value>::type * = nullptr)
        : Describable(ValueWrapper(value))
        {}
        
        const std::string &name(void) const;
        Column at(const std::string &table) const;
        
        Column &as(const std::string & alias);
        
        operator ColumnList(void) const;
        
        bool operator ==(const Column &column) const;
        bool operator !=(const Column &column) const;
    };
}

#endif /* column_hpp */

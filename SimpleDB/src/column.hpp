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

namespace SDB {
    class Column : public Describable {
        
    public:
        static const Column all;
        static const Column row_id;
        
        Column();
        Column(const char *name);
        Column(const std::string &name);
        const std::string &get_name() const;
        Column in_table(const std::string &table) const;
        
        Column &as(const std::string & alias);
        
        operator ColumnList() const;
        
        bool operator ==(const Column &column) const;
        bool operator !=(const Column &column) const;
    };
}

#endif /* column_hpp */

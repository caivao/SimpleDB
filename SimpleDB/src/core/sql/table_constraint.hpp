//
//  table_constraint.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef table_constraint_hpp
#define table_constraint_hpp

#include "declare.hpp"
#include "describable.hpp"
#include "column_index.hpp"
#include "conflict.hpp"

namespace SDB {
    
    class TableConstraint : public Describable {
    public:
        TableConstraint(void);
        TableConstraint(const char *name);
        TableConstraint(const std::string &name);
        
        template <typename T = ColumnIndex>
        typename std::enable_if<std::is_base_of<ColumnIndex, T>::value,
        TableConstraint &>::type
        make_primary(const std::list<const T> &column_index_list)
        {
            _description.append(" PRIMARY KEY(");
            join_component(column_index_list);
            _description.append(")");
            return *this;
        }
        
        template <typename T = ColumnIndex>
        typename std::enable_if<std::is_base_of<ColumnIndex, T>::value,
        TableConstraint &>::type
        make_unique(const std::list<const T> &column_index_list)
        {
            _description.append(" UNIQUE (");
            join_component(column_index_list);
            _description.append(")");
            return *this;
        }
        
        TableConstraint &on_conflict(Conflict conflict);
        TableConstraint &make_check(const Expr &expr);
    };
    
}

#endif /* table_constraint_hpp */

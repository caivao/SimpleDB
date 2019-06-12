//
//  statement_create_index.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_create_index_hpp
#define statement_create_index_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "expr.hpp"
#include "column_index.hpp"

namespace SDB {
    namespace STMT {
        class CreateIndex : public Statement {
            CreateIndex &create(const std::string &index, bool unique = false, bool if_not_exists = true);

            template <typename T = ColumnIndex>
            typename std::enable_if<std::is_base_of<ColumnIndex, T>::value,
            CreateIndex &>::type
            on(const std::string &table, const std::list<const T> &index_list)
            {
                _description.append(" ON " + table + "(");
                component_join(index_list);
                _description.append(")");
                return *this;
            }
            
            CreateIndex &where(const Expr &expr);
        };
    }
}

#endif /* statement_create_index_hpp */

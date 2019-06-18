//
//  statement_insert.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_insert_hpp
#define statement_insert_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "conflict.hpp"
#include "column.hpp"

namespace SDB {
    namespace STMT {
        class Insert : public Statement {
        public:
            template <typename T = Column>
            typename std::enable_if<std::is_base_of<Column, T>::value,
            Insert &>::type
            insert(const std::string &table,
                   const std::list<const T> &column_list = {},
                   const Conflict &conflict = Conflict::replace)
            {
                _description.append("INSERT");
                if (conflict != Conflict::none) {
                    _description.append(" OR ");
                    _description.append(conflict.conflict());
                }
                _description.append(" INTO " + table);
                if (!column_list.empty()) {
                    _description.append("(");
                    join_component(column_list);
                    _description.append(")");
                }
                return *this;
            }
            
            template <typename T = Expr>
            typename std::enable_if<std::is_base_of<Expr, T>::value,
            Insert &>::type
            values(const ExprList &expr_list)
            {
                if (!expr_list.empty()) {
                    _description.append(" VALUES(");
                    join_component(expr_list);
                    _description.append(")");
                }
                return *this;
            }
        };
    }
}

#endif /* statement_insert_hpp */

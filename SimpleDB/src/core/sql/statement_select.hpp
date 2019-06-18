//
//  statement_select.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_select_hpp
#define statement_select_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    
    namespace STMT {
        class Select : public Statement {
        public:
            template <typename T = Column>
            typename std::enable_if<std::is_base_of<Column, T>::value,
            Select &>::type
            select(const std::list<const T> &column_list, bool distinct = false)
            {
                _description.append("SELECT ");
                if (distinct) {
                    _description.append("DISTINCT ");
                }
                join_component(column_list);
                return *this;
            }
            
            template <typename T = NestedQuery>
            typename std::enable_if<std::is_base_of<NestedQuery, T>::value,
            Select &>::type
            from(const std::list<const T> &query_list)
            {
                _description.append(" FROM ");
                join_component(query_list);
                return *this;
            }
            
            Select &from(const Join &join);
            Select &from(const std::string &table);
            Select &where(const Expr &where);
            
            template <typename T = Order>
            typename std::enable_if<std::is_base_of<Order, T>::value,
            Select &>::type
            order_by(const std::list<const T> &order_list)
            {
                if (!order_list.empty()) {
                    _description.append(" ORDER BY ");
                    join_component(order_list);
                }
                return *this;
            }
            
            Select &limit(const Expr &from, const Expr &to);
            Select &limit(const Expr &limit);
            Select &offset(const Expr & offset);
            
            template <typename T = Expr>
            typename std::enable_if<std::is_base_of<Expr, T>::value,
            Select &>::type
            group_by(const std::list<const T> &group_list)
            {
                if (!group_list.empty()) {
                    _description.append(" GROUP BY ");
                    join_component(group_list);
                }
                return *this;
            }
            
            Select &having(const Expr &having);
        };
    }
    
}

#endif /* statement_select_hpp */

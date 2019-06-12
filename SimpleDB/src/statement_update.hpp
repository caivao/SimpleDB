//
//  statement_update.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_update_hpp
#define statement_update_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "expr.hpp"
#include "conflict.hpp"

namespace SDB {
    
    namespace STMT {
        class Update : public Statement {
        public:
            Update &update(const std::string &table, Conflict conflict = Conflict::none);
            
            template <typename T, typename U>
            typename std::enable_if<std::is_base_of<Column, T>::value &&
            std::is_base_of<Expr, U>::value,
            Update &>::type
            set(const std::list<const std::pair<const T, const U>> &value_list)
            {
                _description.append(" SET ");
                bool flag = false;
                for (const auto &value : value_list) {
                    if (flag) {
                        _description.append(", ");
                    } else {
                        flag = true;
                    }
                    _description.append(value.first.get_description() + "=" + value.second.get_description());
                }
                return *this;
            }
            
            Update &where(const Expr &where);

            template <typename T = Order>
            typename std::enable_if<std::is_base_of<Order, T>::value,
            Update &>::type
            order_by(const OrderList &order_list)
            {
                if (!order_list.empty()) {
                    _description.append(" ORDER BY ");
                    component_join(order_list);
                }
                return *this;
            }
            
            Update &limit(const Expr &from, const Expr &to);
            Update &limit(const Expr &limit);
            Update &offset(const Expr &offset);
        };
    }
}

#endif /* statement_update_hpp */

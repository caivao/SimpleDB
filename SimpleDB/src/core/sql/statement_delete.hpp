//
//  statement_delete.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_delete_hpp
#define statement_delete_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class Delete : public Statement {
        public:
            Delete &delete_from(const std::string &table);
            Delete &where(const Expr &expr);
            
            template <typename T = Order>
            typename std::enable_if<std::is_base_of<Order, T>::value,
            Delete &>::type
            order_by(const std::list<const T> &order_list)
            {
                if (!order_list.empty()) {
                    _description.append(" ORDER BY ");
                    join_component(order_list);
                }
                return *this;
            }
            
            Delete &limit(const Expr &from, const Expr &to);
            Delete &limit(const Expr &expr);
            Delete &offset(const Expr &expr);
        };
    }
}

#endif /* statement_delete_hpp */

//
//  join.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "join.hpp"
#include "expr.hpp"
#include "column.hpp"
#include "nested_query.hpp"

namespace SDB {
    
    Join::Join()
    : Describable("")
    {}
    
    Join::Join(const std::string &table)
    : Describable(table)
    {}
    
    Join &Join::join(const NestedQuery &query, Type type, bool is_natural)
    {
        if (is_natural) {
            _description.append(" NATURAL");
        }
        if (type != Type::none) {
            switch (type) {
                case Type::left:
                    _description.append(" LEFT");
                    break;
                case Type::left_outer:
                    _description.append(" LEFT OUTER");
                    break;
                case Type::inner:
                    _description.append(" INNER");
                    break;
                case Type::cross:
                    _description.append(" CROSS");
                    break;
                default:
                    break;
            }
        }
        _description.append(" JOIN " + query.get_description());
        return *this;
    }
    
    Join &Join::on(const Expr &expr)
    {
        _description.append(" ON " + expr.get_description());
        return *this;
    }
    
}

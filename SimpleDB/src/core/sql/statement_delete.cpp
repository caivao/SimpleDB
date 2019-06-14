//
//  statement_delete.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_delete.hpp"
#include "expr.hpp"
#include "order.hpp"

namespace SDB {
    namespace STMT {
        Delete &Delete::delete_from(const std::string &table)
        {
            _description.append("DELETE FROM " + table);
            return *this;
        }
        
        Delete &Delete::where(const Expr &where)
        {
            if (!where.empty()) {
                _description.append(" WHERE " + where.description());
            }
            return *this;
        }
        
        Delete &Delete::limit(const Expr &from, const Expr &to)
        {
            if (!from.empty()) {
                _description.append(" LIMIT " + from.description());
                if (!to.empty()) {
                    _description.append("," + to.description());
                }
            }
            return *this;
        }
        
        Delete &Delete::limit(const Expr &limit)
        {
            if (!limit.empty()) {
                _description.append(" LIMIT " + limit.description());
            }
            return *this;
        }
        
        Delete &Delete::offset(const Expr &offset)
        {
            if (!offset.empty()) {
                _description.append(" OFFSET " + offset.description());
            }
            return *this;
        }
    }
    
}

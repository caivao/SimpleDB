//
//  statement_update.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_update.hpp"
#include "order.hpp"

namespace SDB {
    
    namespace STMT {
        Update &Update::update(const std::string &table, Conflict conflict)
        {
            _description.append("UPDATE ");
            if (conflict != Conflict::none) {
                _description.append("OR ");
                _description.append(conflict.conflict());
                _description.append(" ");
            }
            _description.append(table);
            return *this;
        }
        
        Update &Update::where(const Expr &where)
        {
            if (!where.empty()) {
                _description.append(" WHERE " + where.description());
            }
            return *this;
        }
        
        Update &Update::limit(const Expr &from, const Expr &to)
        {
            if (!from.empty()) {
                _description.append(" LIMIT " + from.description());
                if (!to.empty()) {
                    _description.append("," + to.description());
                }
            }
            return *this;
        }
        
        Update &Update::limit(const Expr &limit)
        {
            if (!limit.empty()) {
                _description.append(" LIMIT " + limit.description());
            }
            return *this;
        }
        
        Update &Update::offset(const Expr &offset)
        {
            if (!offset.empty()) {
                _description.append(" OFFSET " + offset.description());
            }
            return *this;
        }
    }
    
}

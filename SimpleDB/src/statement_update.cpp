//
//  statement_update.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
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
                _description.append(conflict.get_conflict());
                _description.append(" ");
            }
            _description.append(table);
            return *this;
        }
        
        Update &Update::where(const Expr &where)
        {
            if (!where.empty()) {
                _description.append(" WHERE " + where.get_description());
            }
            return *this;
        }
        
        Update &Update::limit(const Expr &from, const Expr &to)
        {
            if (!from.empty()) {
                _description.append(" LIMIT " + from.get_description());
                if (!to.empty()) {
                    _description.append("," + to.get_description());
                }
            }
            return *this;
        }
        
        Update &Update::limit(const Expr &limit)
        {
            if (!limit.empty()) {
                _description.append(" LIMIT " + limit.get_description());
            }
            return *this;
        }
        
        Update &Update::offset(const Expr &offset)
        {
            if (!offset.empty()) {
                _description.append(" OFFSET " + offset.get_description());
            }
            return *this;
        }
    }
    
}

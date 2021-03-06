//
//  statement_select.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_select.hpp"
#include "nested_query.hpp"
#include "join.hpp"
#include "order.hpp"
#include "expr.hpp"
#include "column.hpp"

namespace SDB {
    
    namespace STMT {
        
        Select &Select::from(const Join &join)
        {
            _description.append(" FROM " + join.description());
            return *this;
        }
        
        Select &Select::from(const std::string &table)
        {
            _description.append(" FROM " + table);
            return *this;
        }
        
        Select &Select::where(const Expr &where)
        {
            if (!where.empty()) {
                _description.append(" WHERE " + where.description());
            }
            return *this;
        }
        
        Select &Select::limit(const Expr &from, const Expr &to)
        {
            if (!from.empty()) {
                _description.append(" LIMIT " + from.description());
                if (!to.empty()) {
                    _description.append("," + to.description());
                }
            }
            return *this;
        }
        
        Select &Select::limit(const Expr &limit)
        {
            if (!limit.empty()) {
                _description.append(" LIMIT " + limit.description());
            }
            return *this;
        }
        
        Select &Select::offset(const Expr &offset)
        {
            if (!offset.empty()) {
                _description.append(" OFFSET " + offset.description());
            }
            return *this;
        }
        
        Select &Select::having(const Expr &having)
        {
            if (!having.empty()) {
                _description.append(" HAVING " + having.description());
            }
            return *this;
        }
    }
    
}

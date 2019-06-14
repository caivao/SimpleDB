//
//  statement_attach.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_attach.hpp"
#include "expr.hpp"

namespace SDB {
    
    namespace STMT {
        Attach &Attach::attach(const Expr &expr, const std::string &database)
        {
            _description.append("ATTACH " + database + " " + expr.description());
            return *this;
        }
        
        Attach &Attach::as(const std::string &schema)
        {
            _description.append(" AS " + schema);
            return *this;
        }
    }
    
}

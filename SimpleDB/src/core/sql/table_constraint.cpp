//
//  table_constraint.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "table_constraint.hpp"
#include "expr.hpp"

namespace SDB {
    
    TableConstraint::TableConstraint()
    : Describable("")
    {}
    
    TableConstraint::TableConstraint(const char *name)
    : Describable(std::string("CONSTRAINT ") + name)
    {}
    
    TableConstraint::TableConstraint(const std::string &name)
    : Describable("CONSTRAINT " + name)
    {}
    
    TableConstraint &TableConstraint::on_conflict(Conflict conflict)
    {
        if (conflict != Conflict::none) {
            _description.append(" ON CONFLICT ");
            _description.append(conflict.get_conflict());
        }
        return *this;
    }
    
    TableConstraint &TableConstraint::make_check(const Expr &expr)
    {
        _description.append(" CHECK (" + expr.get_description() + ")");
        return *this;
    }
    
}

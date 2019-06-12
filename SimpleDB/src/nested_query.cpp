//
//  nested_query.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "nested_query.hpp"
#include "statement_select.hpp"
#include "join.hpp"

namespace SDB {
    
    NestedQuery::NestedQuery(const char *table) : Describable(table)
    {}
    
    NestedQuery::NestedQuery(const std::string &table) : Describable(table)
    {}
    
    NestedQuery::NestedQuery(const Join &join)
    : Describable("(" + join.get_description() + ")")
    {}
    
    NestedQuery::NestedQuery(const STMT::Select &select)
    : Describable("(" + select.sql() + ")")
    {}
    
    NestedQuery &NestedQuery::as(const std::string &alias)
    {
        _description.append(" AS " + alias);
        return *this;
    }
    
    NestedQuery::operator NestedQueryList() const
    {
        return {*this};
    }
    
}

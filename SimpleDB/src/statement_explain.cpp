//
//  statement_explain.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_explain.hpp"

namespace SDB {
    namespace STMT {
        Explain &Explain::explain(const Statement &statement, bool query_plan)
        {
            if(query_plan) {
                _description.append("EXPLAIN QUERY PLAN" + statement.get_description());
            } else {
                _description.append("EXPLAIN " + statement.get_description());
            }
            return *this;
        }
    }
}

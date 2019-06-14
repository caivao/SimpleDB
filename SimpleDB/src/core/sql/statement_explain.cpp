//
//  statement_explain.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_explain.hpp"

namespace SDB {
    namespace STMT {
        Explain &Explain::explain(const Statement &statement, bool query_plan)
        {
            if(query_plan) {
                _description.append("EXPLAIN QUERY PLAN" + statement.description());
            } else {
                _description.append("EXPLAIN " + statement.description());
            }
            return *this;
        }
    }
}

//
//  statement_explain.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_explain_hpp
#define statement_explain_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class Explain : public Statement {
        public:
            Explain &explain(const Statement &statement, bool query_plan = false);
        };
    }
}

#endif /* statement_explain_hpp */

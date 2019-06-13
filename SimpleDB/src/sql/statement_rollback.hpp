//
//  statement_rollback.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_rollback_hpp
#define statement_rollback_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class Rollback : public Statement {
        public:
            Rollback &rollback(const std::string & point);
            
            virtual Statement::Flag flag(void) const override;
        };
    }
}

#endif /* statement_rollback_hpp */

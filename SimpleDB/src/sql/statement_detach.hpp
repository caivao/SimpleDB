//
//  statement_detach.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_detach_hpp
#define statement_detach_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class Detach : public Statement {
        public:
            Detach &detach(const std::string &schema, const std::string &database = "");
            
            virtual Statement::Flag flag(void) const override;
        };
    }
}

#endif /* statement_detach_hpp */

//
//  statement_vacuum.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_vacuum_hpp
#define statement_vacuum_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class Vacuum : public Statement {
        public:
            Vacuum &vacuum(const std::string & schema);
        };
    }
}

#endif /* statement_vacuum_hpp */

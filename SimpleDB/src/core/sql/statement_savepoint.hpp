//
//  statement_savepoint.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_savepoint_hpp
#define statement_savepoint_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class SavePoint : public Statement {
        public:
            SavePoint &save_point(const std::string & point);
        };
    }
}

#endif /* statement_savepoint_hpp */

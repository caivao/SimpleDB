//
//  statement_drop_index.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_drop_index_hpp
#define statement_drop_index_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class DropIndex : public Statement {
            DropIndex drop(const std::string &index, bool if_exists = true);
        };
    }
}

#endif /* statement_drop_index_hpp */

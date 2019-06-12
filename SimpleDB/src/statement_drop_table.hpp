//
//  statement_drop_table.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_drop_table_hpp
#define statement_drop_table_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    namespace STMT {
        class DropTable : public Statement {
            DropTable drop(const std::string &table, bool if_exists = true);
        };
    }
}

#endif /* statement_drop_table_hpp */

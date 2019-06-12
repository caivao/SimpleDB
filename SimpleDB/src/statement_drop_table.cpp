//
//  statement_drop_table.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_drop_table.hpp"

namespace SDB {
    namespace STMT {
        DropTable DropTable::drop(const std::string &table, bool if_exists)
        {
            _description.append("DROP TABLE ");
            if (if_exists) {
                _description.append("IF EXISTS ");
            }
            _description.append(table);
            return *this;
        }
    }
}

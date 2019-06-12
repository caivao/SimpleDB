//
//  statement_create_table.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_create_table.hpp"

namespace SDB {
    namespace STMT {
        CreateTable &CreateTable::create(const std::string && table, bool if_not_exists)
        {
            _description.append("CREATE TABLE ");
            if (if_not_exists) {
                _description.append("IF NOT EXISTS ");
            }
            _description.append(table);
            return *this;
        }
    }
}

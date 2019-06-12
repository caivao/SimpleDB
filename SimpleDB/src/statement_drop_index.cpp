//
//  statement_drop_index.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_drop_index.hpp"

namespace SDB {
    namespace STMT {
        DropIndex DropIndex::drop(const std::string &index, bool if_exists)
        {
            _description.append("DROP INDEX ");
            if (if_exists) {
                _description.append("IF EXISTS ");
            }
            _description.append(index);
            return *this;
        }
    }
}

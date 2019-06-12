//
//  statement_rollback.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_rollback.hpp"

namespace SDB {
    namespace STMT {
        Rollback &Rollback::rollback(const std::string & point)
        {
            _description.append("ROLLBACK TO " + point);
            return *this;
        }
    }
}

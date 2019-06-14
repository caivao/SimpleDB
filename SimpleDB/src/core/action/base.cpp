//
//  base.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "base.hpp"
#include "sql.hpp"
#include "utils.hpp"

namespace SDB {
    bool Base::exec(const STMT::Statement &stmt, Error &error)
    {
        bool result = false;
//        if (handle) {
//            result = handle->exec(statement);
//            error = handle->getError();
//        }
        return result;
    }
}

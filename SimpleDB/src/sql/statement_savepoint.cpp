//
//  statement_savepoint.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_savepoint.hpp"

namespace SDB {
    namespace STMT {
        SavePoint &SavePoint::save_point(const std::string & name)
        {
            _description.append("ROLLBACK TO " + name);
            return *this;
        }
        
        Statement::Flag SavePoint::flag(void) const
        {
            return Statement::Flag::savepoint;
        }
    }
}

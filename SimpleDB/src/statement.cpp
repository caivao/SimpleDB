//
//  statement.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement.hpp"

namespace SDB {
    namespace STMT {
        Statement::Statement()
        : Describable("")
        {}
        
        const std::string &Statement::sql(void) const
        {
            return _description;
        }
        
//        Statement::~Statement()
//        {}
    }
}

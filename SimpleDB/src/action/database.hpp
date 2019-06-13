//
//  database.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include "declare.hpp"
#include "base.hpp"

namespace SDB {
    class Database : public Base {
        bool exec(const STMT::Statement &stmt, Error &error) override;
    };
}

#endif /* database_hpp */

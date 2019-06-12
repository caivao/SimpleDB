//
//  statement_detach.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_detach.hpp"

namespace SDB {
    namespace STMT {
        Detach &Detach::detach(const std::string &schema, const std::string &database)
        {
            _description.append("DETACH " + database + " " + schema);
            return *this;
        }
    }
}

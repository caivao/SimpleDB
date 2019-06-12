//
//  statement_vacuum.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_vacuum.hpp"

namespace SDB {
    namespace STMT {
//        Vacuum &Vacuum::vacuum(const char * schema)
//        {
//            return vacuum(schema ? std::string(schema) : "");
//        }
        
        Vacuum &Vacuum::vacuum(const std::string & schema)
        {
            _description.append("VACUUM " + schema);
            return *this;
        }
    }
}

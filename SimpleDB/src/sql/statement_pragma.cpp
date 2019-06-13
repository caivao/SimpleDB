//
//  statement_pragma.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_pragma.hpp"

namespace SDB {
    
    namespace STMT {
        Pragma &Pragma::pragma(const SDB::Pragma &pragma)
        {
            _description.append("PRAGMA " + pragma.get_name());
            return *this;
        }
        
        Pragma &Pragma::operator =(const char *value)
        {
            if(!value) {
                _description.append(" = 0");
            } else {
                _description.append(" = " + ValueWrapper(value).get_description());
            }
            
            return *this;
        }
        
        Statement::Flag Pragma::flag(void) const
        {
            return Statement::Flag::pragma;
        }
    }
    
}

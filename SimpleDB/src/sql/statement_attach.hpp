//
//  statement_attach.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_attach_hpp
#define statement_attach_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    
    namespace STMT {
        class Attach : public Statement {
        public:
            Attach &attach(const Expr &expr, const std::string &database = "");
            Attach &as(const std::string &schema);
            
            virtual Statement::Flag flag(void) const override;
        };
    }
    
}

#endif /* statement_attach_hpp */

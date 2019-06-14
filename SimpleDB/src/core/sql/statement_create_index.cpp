//
//  statement_create_index.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_create_index.hpp"

namespace SDB {
    namespace STMT {
        CreateIndex &CreateIndex::create(const std::string &index, bool unique, bool if_not_exists)
        {
            _description.append("CREATE ");
            if (unique) {
                _description.append("UNIQUE ");
            }
            _description.append("INDEX ");
            if (if_not_exists) {
                _description.append("IF NOT EXISTS ");
            }
            _description.append(index);
            return *this;
        }
        
        CreateIndex &CreateIndex::where(const Expr &expr)
        {
            if(!expr.empty()) {
                _description.append(" WHERE " + expr.description());
            }
            return *this;
        }
    }
}

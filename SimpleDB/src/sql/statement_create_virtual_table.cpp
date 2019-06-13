//
//  statement_create_virtual_table.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/7.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_create_virtual_table.hpp"


namespace SDB {
    
    namespace STMT {
        CreateVirtualTable &CreateVirtualTable::create(const std::string &table, bool if_not_exists)
        {
            _description.append("CREATE VIRTUAL TABLE ");
            if (if_not_exists) {
                _description.append("IF NOT EXISTS ");
            }
            _description.append(table);
            return *this;
        }
        
        CreateVirtualTable &CreateVirtualTable::using_module(const std::string &module)
        {
            _description.append(" USING " + module);
            return *this;
        }
        
        Statement::Flag CreateVirtualTable::flag() const
        {
            return Statement::Flag::create_vitual_table;
        }
    }
    
}

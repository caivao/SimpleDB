//
//  statement_alter_table.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_alter_table.hpp"

namespace SDB {
    namespace STMT {
        AlterTable &AlterTable::alter(const std::string &table)
        {
            _description.append("ALTER TABLE " + table);
            return *this;
        }
        
        AlterTable &AlterTable::rename(const std::string &new_name)
        {
            _description.append(" RENAME TO " + new_name);
            return *this;
        }
        
        AlterTable &AlterTable::add_column(const ColumnDef &column_def)
        {
            _description.append(" ADD COLUMN " + column_def.get_description());
            return *this;
        }
    }
}

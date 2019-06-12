//
//  statement_alter_table.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_alter_table_hpp
#define statement_alter_table_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "column.hpp"
#include "column_def.hpp"

namespace SDB {
    namespace STMT {
        class AlterTable : public Statement {
            
            /// 修改表
            AlterTable &alter(const std::string &table);
            /// 重命名表
            AlterTable &rename(const std::string &new_table);
            /// 添加列
            AlterTable &add_column(const ColumnDef &column_def);
        };
    }
}

#endif /* statement_alter_table_hpp */

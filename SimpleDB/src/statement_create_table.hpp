//
//  statement_create_table.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_create_table_hpp
#define statement_create_table_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "column.hpp"
#include "column_def.hpp"

namespace SDB {
    namespace STMT {
        class CreateTable : public Statement {
        public:
            /// 创建表
            CreateTable &create(const std::string && table, bool if_not_exists = true);
            
            template <typename T = ColumnDef>
            typename std::enable_if<std::is_base_of<ColumnDef, T>::value,
            CreateTable &>::type
            create(const std::string &table,
                   const std::list<const T> &column_defs,
                   bool if_not_exists = true)
            {
                _description.append("CREATE TABLE ");
                if (if_not_exists) {
                    _description.append("IF NOT EXISTS ");
                }
                _description.append(table + "(");
                component_join(column_defs);
                _description.append(")");
                return *this;
            }
        };
    }
}

#endif /* statement_create_table_hpp */

//
//  statement_create_virtual_table.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/7.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_create_virtual_table_hpp
#define statement_create_virtual_table_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    
    namespace STMT {
        class CreateVirtualTable : public Statement {
        public:
            CreateVirtualTable &create(const std::string &table, bool if_not_exists = true);
            
            CreateVirtualTable &using_module(const std::string &module);
            
            template <typename T = ModuleArgument>
            typename std::enable_if<std::is_base_of<ModuleArgument, T>::value,
            CreateVirtualTable &>::type
            using_module(const std::string &module, const std::list<T> &module_argument_list)
            {
                _description.append(" USING " + module);
                if (!module_argument_list.empty()) {
                    _description.append("(");
                    component_join(module_argument_list);
                    _description.append(")");
                }
                return *this;
            }
        };
    }
    
}

#endif /* statement_create_virtual_table_hpp */

//
//  module_argument.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "module_argument.hpp"
#include "table_constraint.hpp"
#include "column_def.hpp"

namespace SDB {
    
    ModuleArgument::ModuleArgument(const TableConstraint &table_constraint)
    : Describable(table_constraint.description())
    {}
    
    ModuleArgument::ModuleArgument(const ColumnDef &column_def)
    : Describable(column_def.description())
    {}
    
    ModuleArgument::ModuleArgument(const std::string &lhs, const std::string &rhs)
    : Describable(lhs + "=" + rhs)
    {}
    
}

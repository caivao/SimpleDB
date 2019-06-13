//
//  module_argument.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef module_argument_hpp
#define module_argument_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    
    class ModuleArgument : public Describable {
    public:
        ModuleArgument(const TableConstraint &table_constraint);
        ModuleArgument(const ColumnDef &column_def);
        ModuleArgument(const std::string &lhs, const std::string &rhs);
    };
    
}

#endif /* module_argument_hpp */

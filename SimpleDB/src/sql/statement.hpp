//
//  statement.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_hpp
#define statement_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    namespace STMT {
        class Statement : public Describable {
        public:
            enum class Flag: int {
                unknown,
                create_table,
                create_vitual_table,
                drop_table,
                alter_table,
                create_index,
                drop_index,
                insert,
                deletee,
                update,
                select,
                transaction,
                pragma,
                vacuum,
                attach,
                detach,
                rollback,
                savepoint,
                explain
            };
            
            Statement();
            const std::string &sql(void) const;
            virtual Flag flag(void) const = 0;
            virtual ~Statement();
        };
    }
}

#endif /* statement_hpp */

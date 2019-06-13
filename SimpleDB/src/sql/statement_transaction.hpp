//
//  statement_transaction.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_transaction_hpp
#define statement_transaction_hpp

#include "declare.hpp"
#include "statement.hpp"

namespace SDB {
    
    namespace STMT {
        class Transaction : public Statement {
        public:
            enum class Mode : int {
                defered,
                immediate,
                exclusive,
            };
            enum class State : int {
                none,
                begin,
                commit,
                rollback,
            };
            
            Transaction &begin(Mode mode = Mode::immediate);
            Transaction &commit();
            Transaction &rollback();
            
            const Transaction::State &get_state() const;
            
            virtual Statement::Flag flag(void) const override;
            
        protected:
            Transaction::State _type;
        };
    }
    
}

#endif /* statement_transaction_hpp */

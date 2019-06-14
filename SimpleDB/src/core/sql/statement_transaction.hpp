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
                begin,
                commit,
                rollback,
            };
            
            Transaction &begin(Mode mode = Mode::immediate);
            Transaction &commit();
            Transaction &rollback();
            
            const Transaction::State &get_state() const;
            
            std::shared_ptr<ValueBinder> prepare(const void *context, Tracer &tracer, Error &error) const override;
            bool exec(const void *context, Tracer &tracer, Error &error) const override;
            
        protected:
            Transaction::State _state;
        };
    }
    
}

#endif /* statement_transaction_hpp */

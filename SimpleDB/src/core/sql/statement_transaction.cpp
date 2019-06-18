//
//  statement_transaction.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_transaction.hpp"
#include "value_binder.hpp"
#include "tracer.hpp"

namespace SDB {
    
    namespace STMT {
        Transaction &Transaction::begin(Mode mode)
        {
            _state = State::begin;
            _description.append("BEGIN");
            switch (mode) {
                case Mode::immediate:
                    _description.append(" IMMEDIATE");
                    break;
                case Mode::exclusive:
                    _description.append(" EXCLUSIVE");
                default:
                    break;
            }
            return *this;
        }
        
        Transaction &Transaction::commit(void)
        {
            _state = State::commit;
            _description.append("COMMIT");
            return *this;
        }
        
        Transaction &Transaction::rollback(void)
        {
            _state = State::rollback;
            _description.append("ROLLBACK");
            return *this;
        }
        
        const Transaction::State &Transaction::state(void) const
        {
            return _state;
        }
        
        std::shared_ptr<ValueBinder> Transaction::prepare(const void *, Tracer &, Error &error) const
        {
            Error::report("[prepare] a transaction is not allowed, use [exec] instead", -1, &error);
            return nullptr;
        }
        
        bool Transaction::exec(const void *context, Tracer &tracer, Error &error) const
        {
            bool result = Statement::exec(context, tracer, error);
            switch (_state) {
                case State::begin:
                    if (result) {
                        tracer.enter_transaction();
                    } break;
                case State::commit:
                    if (result) {
                        tracer.exit_transaction();
                    } break;
                case State::rollback:
                    tracer.exit_transaction();
                    break;
            }
            return result;
        }
    }
    
}

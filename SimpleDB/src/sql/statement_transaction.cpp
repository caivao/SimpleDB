//
//  statement_transaction.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_transaction.hpp"

namespace SDB {
    
    namespace STMT {
        Transaction &Transaction::begin(Mode mode)
        {
            _type = State::begin;
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
        
        Transaction &Transaction::commit()
        {
            _type = State::commit;
            _description.append("COMMIT");
            return *this;
        }
        
        Transaction &Transaction::rollback()
        {
            _type = State::rollback;
            _description.append("ROLLBACK");
            return *this;
        }
        
        const Transaction::State &Transaction::get_state() const
        {
            return _type;
        }
        
        Statement::Flag Transaction::flag(void) const
        {
            return Statement::Flag::transaction;
        }
    }
    
}

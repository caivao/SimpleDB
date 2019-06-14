//
//  base.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include "declare.hpp"
#include "handle_pool.hpp"
#include "utils.hpp"

namespace SDB {
    class Base {
    public:
        const std::string &path(void) const;
        virtual StatementReleasable prepare(HandleReleasable &handle, const STMT::Statement &stmt, Error &error) = 0;
        virtual bool exec(HandleReleasable &handle, const STMT::Statement &stmt, Error &error) = 0;
        virtual bool table_exists(HandleReleasable &handle, const std::string &table, Error &error);
        
        typedef std::function<void(Error &)> TransactionAction;
        
        virtual bool begin(STMT::Transaction::Mode mode, Error &error) = 0;
        virtual bool commit(Error &error) = 0;
        virtual bool rollback(Error &error) = 0;
        virtual bool nested_transaction(TransactionAction transaction, Error &error) = 0;
        
    protected:
        Base(const HandlePoolReleasable &pool);
        HandlePoolReleasable _pool;
        
    };
}

#endif /* base_hpp */

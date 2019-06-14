//
//  base.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "base.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include "action.hpp"

namespace SDB {
    Base::Base(const HandlePoolReleasable &pool)
    :_pool(pool)
    {}
    
    const std::string &Base::path(void) const
    {
        return _pool->_path;
    }
    StatementReleasable Base::prepare(HandleReleasable &handle, const STMT::Statement &stmt, Error &error)
    {
        std::shared_ptr<ValueBinder> binder = nullptr;
        if (handle) {
            binder = handle->prepare(stmt);
            error = handle->error();
        }
        return StatementReleasable(handle, binder);
    }
    
    bool Base::exec(HandleReleasable &handle, const STMT::Statement &stmt, Error &error)
    {
        bool result = false;
        if (handle) {
            result = handle->exec(stmt);
            error = handle->error();
        }
        return result;
    }
    
    bool Base::table_exists(HandleReleasable &handle, const std::string &table, Error &error)
    {
        bool result = false;
        if (handle) {
//            Error::setThreadedSlient(true);
            STMT::Select select = STMT::Select().select({ Column("name") })
            .from("sql_master")
            .where((Expr(Column("type")) == "table") && (Expr(Column("name")) == table))
            .limit(1);
            std::shared_ptr<ValueBinder> binder = handle->prepare(select);
//            Error::setThreadedSlient(false);
            if (binder) {
                if(binder->ok()) {
                    result = binder->step();
                } else {
                    error = binder->error();
                }
            } else {
                error = handle->error();
            }
        }
        return result;
    }
}

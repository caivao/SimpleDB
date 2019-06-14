//
//  statement.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement.hpp"
#include "error.hpp"
#include "value_binder.hpp"
#include <sqlite3.h>

namespace SDB {
    namespace STMT {
        Statement::Statement()
        : Describable("")
        {}
        
        const std::string &Statement::sql(void) const
        {
            return _description;
        }
        
        std::shared_ptr<ValueBinder> Statement::prepare(const void *context, Tracer &tracer, Error &error) const
        {
            sqlite3_stmt *stmt = nullptr;
            sqlite3 *ctx = (sqlite3 *)context;
            int rc = sqlite3_prepare_v2(ctx, sql().c_str(), -1, &stmt, nullptr);
            if (rc == SQLITE_OK) {
                error.reset();
                return std::shared_ptr<ValueBinder>(new ValueBinder(stmt));
            }
            Error::report(sqlite3_errmsg(ctx), sqlite3_extended_errcode(ctx), &error);
            return nullptr;
        }
        
        bool Statement::exec(const void *context, Tracer &tracer, Error &error) const
        {
            sqlite3 *ctx = (sqlite3 *)context;
            int rc = sqlite3_exec(ctx, this->sql().c_str(), nullptr, nullptr, nullptr);
            bool result = rc == SQLITE_OK;
            if (result) {
                error.reset();
                return true;
            }
            Error::report(sqlite3_errmsg(ctx), sqlite3_extended_errcode(ctx), &error);
            return false;
        }
        
        Statement::~Statement()
        {}
    }
}

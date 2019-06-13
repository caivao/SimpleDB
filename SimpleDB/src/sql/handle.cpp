//
//  handle.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "handle.hpp"
#include "statement.hpp"
#include "value_binder.hpp"

namespace SDB {
    Handle::Handle(const std::string &path)
    : _context(nullptr)
    , path(path)
    {}
    
    Handle::~Handle(void)
    {
        close();
    }
    
    bool Handle::open(void)
    {
        return true;
    }
    void Handle::close(void)
    {
        int rc = sqlite3_close((sqlite3 *)_context);
        if (rc == SQLITE_OK) {
            _context = nullptr;
            _error.reset();
            return;
        }
        Error::report(sqlite3_errmsg((sqlite3 *)_context), sqlite3_extended_errcode((sqlite3 *)_context), &_error);
    }
    
    std::shared_ptr<ValueBinder> Handle::prepare(const STMT::Statement &statement)
    {
        sqlite3_stmt *stmt = nullptr;
        int rc = sqlite3_prepare_v2((sqlite3 *)_context, statement.sql().c_str(), -1, &stmt, nullptr);
        if (rc == SQLITE_OK) {
            _error.reset();
            return std::shared_ptr<ValueBinder>(new ValueBinder(stmt, *this));
        }
        Error::report(sqlite3_errmsg((sqlite3 *)_context), sqlite3_extended_errcode((sqlite3 *) _context), &_error);
        return nullptr;
    }
    
    bool Handle::exec(const STMT::Statement &statement)
    {
        int rc = sqlite3_exec((sqlite3 *)_context, statement.sql().c_str(), nullptr, nullptr, nullptr);
        bool result = rc == SQLITE_OK;
//        if (statement.getStatementType() == Statement::Type::Transaction) {
//            const StatementTransaction &transaction =
//            (const StatementTransaction &) statement;
//            switch (transaction.getTransactionType()) {
//                case StatementTransaction::Type::Begin:
//                    if (result) {
//                        m_aggregation = true;
//                    }
//                    break;
//                case StatementTransaction::Type::Commit:
//                    if (result) {
//                        m_aggregation = false;
//                    }
//                    break;
//                case StatementTransaction::Type::Rollback:
//                    m_aggregation = false;
//                    break;
//            }
//        }
        if (result) {
            _error.reset();
            return true;
        }
        Error::report(sqlite3_errmsg((sqlite3 *)_context), sqlite3_extended_errcode((sqlite3 *)_context), &_error);
        return false;
    }
    
    const Error &Handle::get_error(void) const
    {
        return _error;
    }
    
    int Handle::get_changes(void)
    {
        return sqlite3_changes((sqlite3 *)_context);
    }
    
    void Handle::set_performance_trace_handle(const PerformanceTraceHandle &handle)
    {
        _tracer.set(handle, _context);
    }
    void Handle::set_sql_trace_handle(const SQLTraceHandle &handle)
    {
        _tracer.set(handle, _context);
    }
}

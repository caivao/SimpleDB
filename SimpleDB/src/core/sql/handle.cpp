//
//  handle.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "handle.hpp"
#include "statement.hpp"
#include "value_binder.hpp"
#include "statement_transaction.hpp"
#include "utils.hpp"

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
        Error inner_error;
        sqlite3 *ctx = (sqlite3 *)_context;
        File::create_directory_recursive(Path::file_base_name(path), inner_error);
        int rc = sqlite3_open(path.c_str(), &ctx);
        if (rc == SQLITE_OK) {
            _error.reset();
            return true;
        }
        Error::report(sqlite3_errmsg(ctx), sqlite3_extended_errcode(ctx), &_error);
        return false;
    }
    
    void Handle::close(void)
    {
        sqlite3 *ctx = (sqlite3 *)_context;
        int rc = sqlite3_close(ctx);
        if (rc == SQLITE_OK) {
            _context = nullptr;
            _error.reset();
            return;
        }
        Error::report(sqlite3_errmsg(ctx), sqlite3_extended_errcode(ctx), &_error);
    }
    
    std::shared_ptr<ValueBinder> Handle::prepare(const STMT::Statement &statement)
    {
        return statement.prepare(_context, _tracer, _error);
    }
    
    bool Handle::exec(const STMT::Statement &statement)
    {
        return statement.exec(_context, _tracer, _error);
    }
    
    const Error &Handle::get_error(void) const
    {
        return _error;
    }
    
    int Handle::get_changes(void)
    {
        return sqlite3_changes((sqlite3 *)_context);
    }
    
    void Handle::set_tracer_handle(const PerformanceTraceHandle &handle)
    {
        _tracer.set(handle, _context);
    }
    
    void Handle::set_tracer_handle(const SQLTraceHandle &handle)
    {
        _tracer.set(handle, _context);
    }
}

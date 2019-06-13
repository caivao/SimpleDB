//
//  value_binder.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "value_binder.hpp"
#include "handle.hpp"

namespace SDB {
    
    ValueBinder::ValueBinder(void *stmt, const Handle &handle)
    : _stmt(stmt), _handle(handle)
    {}
    
    bool ValueBinder::next(void)
    {
        int rc = sqlite3_step((sqlite3_stmt *)_stmt);
        if (rc == SQLITE_ROW || rc == SQLITE_OK || rc == SQLITE_DONE) {
            _error.reset();
            return rc == SQLITE_ROW;
        }
        sqlite3 *handle = sqlite3_db_handle((sqlite3_stmt *)_stmt);
        Error::report(sqlite3_errmsg(handle), sqlite3_extended_errcode(handle), &_error);
        return false;
    }
    
    void ValueBinder::reset(void)
    {
        int rc = sqlite3_reset((sqlite3_stmt *) _stmt);
        if (rc == SQLITE_OK) {
            _error.reset();
        } else {
            sqlite3 *handle = sqlite3_db_handle((sqlite3_stmt *) _stmt);
            Error::report(sqlite3_errmsg(handle), sqlite3_extended_errcode(handle), &_error);
        }
    }
    
    void ValueBinder::finalize()
    {
        if (_stmt) {
            
            int rc = sqlite3_finalize((sqlite3_stmt *) _stmt);
            _stmt = nullptr;
            if (rc == SQLITE_OK) {
                _error.reset();
                return;
            }
            sqlite3 *handle = sqlite3_db_handle((sqlite3_stmt *) _stmt);
            Error::report(sqlite3_errmsg(handle), sqlite3_extended_errcode(handle), &_error);
        }
    }
    
    void ValueBinder::bind_null(int idx)
    {
        sqlite3_bind_null((sqlite3_stmt *) _stmt, idx);
    }
    
    void ValueBinder::bind_int32(const SQLite_Integer32_Type &value, int idx)
    {
        sqlite3_bind_int((sqlite3_stmt *) _stmt, idx, value);
    }
    
    void ValueBinder::bind_int64(const SQLite_Integer64_Type &value, int idx)
    {
        sqlite3_bind_int64((sqlite3_stmt *) _stmt, idx, value);
    }
    
    void ValueBinder::bind_real(const SQLite_Real_Type &value, int idx)
    {
        sqlite3_bind_double((sqlite3_stmt *) _stmt, idx, value);
    }
    
    void ValueBinder::bind_text(const SQLite_Text_Type &value, int idx)
    {
        sqlite3_bind_text((sqlite3_stmt *) _stmt, idx, value, -1, SQLITE_TRANSIENT);
    }
    
    void ValueBinder::bind_blob(const SQLite_BLOB_Type &value, int size, int idx)
    {
        sqlite3_bind_blob((sqlite3_stmt *) _stmt, idx, value, size, SQLITE_TRANSIENT);
    }
    
    
    SQLite_Integer32_Type ValueBinder::int32_value(int idx)
    {
        return (typename SQLite_Integer32_Type) sqlite3_column_int((sqlite3_stmt *) _stmt, idx);
    }
    
    SQLite_Integer64_Type ValueBinder::int64_value(int idx)
    {
        return (typename SQLite_Integer64_Type) sqlite3_column_int64((sqlite3_stmt *) _stmt, idx);
    }
    
    SQLite_Real_Type ValueBinder::real_value(int idx)
    {
        return (typename SQLite_Real_Type) sqlite3_column_double((sqlite3_stmt *) _stmt, idx);
    }
    
    SQLite_Text_Type ValueBinder::text_value(int idx)
    {
        return (typename SQLite_Text_Type) sqlite3_column_text((sqlite3_stmt *) _stmt, idx);
    }
    
    SQLite_BLOB_Type ValueBinder::blob_value(int idx, int &size)
    {
        size = sqlite3_column_bytes((sqlite3_stmt *)_stmt, idx);
        return (typename SQLite_BLOB_Type) sqlite3_column_blob((sqlite3_stmt *)_stmt, idx);
    }
    
    int ValueBinder::column_count(void) const
    {
        return sqlite3_column_count((sqlite3_stmt *)_stmt);
    }
    
    const char *ValueBinder::column_name(int idx) const
    {
        return sqlite3_column_name((sqlite3_stmt *)_stmt, idx);
    }
    
    const char *ValueBinder::table_name(int idx) const
    {
        return sqlite3_column_table_name((sqlite3_stmt *)_stmt, idx);
    }
    
    
    uint64_t ValueBinder::last_insert_rowid(void) const
    {
        return sqlite3_last_insert_rowid(sqlite3_db_handle((sqlite3_stmt *)_stmt));
    }
    
    
    ValueBinder::~ValueBinder(void)
    {
        finalize();
    }
    
}

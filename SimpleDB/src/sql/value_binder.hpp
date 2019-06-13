//
//  value_binder.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef value_binder_hpp
#define value_binder_hpp

#include <sqlite3.h>
#include "declare.hpp"
#include "column.hpp"
#include "column_def.hpp"
#include "error.hpp"

namespace SDB {
    class ValueBinder {
    public:
        
        bool next(void);
        void reset(void);
        void finalize(void);
        
        /// setter
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::int32_type, void>::type
        bind(const typename ColumnDef::TypeMeta<T>::CType &value, int idx)
        {
            bind_int32(value, idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::int64_type, void>::type
        bind(const typename ColumnDef::TypeMeta<T>::CType &value, int idx)
        {
            bind_int64(value, idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::real_type, void>::type
        bind(const typename ColumnDef::TypeMeta<T>::CType &value, int idx)
        {
            bind_real(value, idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::text_type, void>::type
        bind(const typename ColumnDef::TypeMeta<T>::CType &value, int idx)
        {
            bind_text(value, idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::blob_type, void>::type
        bind(const typename ColumnDef::TypeMeta<T>::CType &value, int size, int idx)
        {
            bind_blob(value, size, idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::null_type, void>::type
        bind(int idx)
        {
            bind_null(idx);
        };
        
        /// getter
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::int32_type,
        typename ColumnDef::TypeMeta<T>::CType>::type
        value(int idx)
        {
            return int32_value(idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::int64_type,
        typename ColumnDef::TypeMeta<T>::CType>::type
        value(int idx)
        {
            return int64_value(idx);
        };
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::real_type,
        typename ColumnDef::TypeMeta<T>::CType>::type
        value(int idx)
        {
            return real_value(idx);
        }
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::text_type,
        typename ColumnDef::TypeMeta<T>::CType>::type
        value(int idx)
        {
            return text_value(idx);
        }
        
        template <ColumnDef::Type T>
        typename std::enable_if<ColumnDef::TypeMeta<T>::blob_type,
        typename ColumnDef::TypeMeta<T>::CType>::type
        value(int idx, int &size)
        {
            return blob_value(idx, size);
        }
        
        int column_count(void) const;
        const char *column_name(int idx) const;
        const char *table_name(int idx) const;
        
        uint64_t last_insert_rowid(void) const;
        
        ~ValueBinder(void);
        
    protected:
        void bind_null(int idx);
        void bind_int32(const SQLite_Integer32_Type &value, int idx);
        void bind_int64(const SQLite_Integer64_Type &value, int idx);
        void bind_real(const SQLite_Real_Type &value, int idx);
        void bind_text(const SQLite_Text_Type &value, int idx);
        void bind_blob(const SQLite_BLOB_Type &value, int size, int idx);
        
        SQLite_Integer32_Type int32_value(int idx);
        SQLite_Integer64_Type int64_value(int idx);
        SQLite_Real_Type real_value(int idx);
        SQLite_Text_Type text_value(int idx);
        SQLite_BLOB_Type blob_value(int idx, int &size);
        
        ValueBinder(void *stmt, const Handle &handle);
        const ValueBinder &operator=(const ValueBinder &other) = delete;
        ValueBinder(const ValueBinder &other) = delete;
        
        void *_stmt;
        const Handle &_handle;
        Error _error;
        
        friend class Handle;
    };
}

#endif /* value_binder_hpp */

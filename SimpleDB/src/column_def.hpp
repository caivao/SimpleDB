//
//  column_def.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef column_def_hpp
#define column_def_hpp

#include "declare.hpp"
#include "describable.hpp"
#include "order.hpp"
#include "conflict.hpp"
#include "expr.hpp"

namespace SDB {
    class ColumnDef : public Describable {
    public:
        enum class Type : int {
            null,
            real,
            integer32,
            integer64,
            text,
            blob
        };
        
        template <typename T, typename Enable = void>
        struct RealCheck : public std::false_type {};
        template <typename T>
        struct RealCheck<T,
        typename std::enable_if<std::is_floating_point<T>::value>::type>
        : public std::true_type { };
        
        template <typename T, typename Enable = void>
        struct Integer32Check : public std::false_type {};
        template <typename T>
        struct Integer32Check< T,
        typename std::enable_if<(std::is_integral<T>::value
                                 || std::is_enum<T>::value)
        && (sizeof(T) <= 4)>::type>
        : public std::true_type {};
        
        template <typename T, typename Enable = void>
        struct Integer64Check : public std::false_type {};
        template <typename T>
        struct Integer64Check<T,
        typename std::enable_if<(std::is_integral<T>::value
                                 || std::is_enum<T>::value)
        && (sizeof(T) > 4)>::type>
        : public std::true_type {};
        
        template <typename T, typename Enable = void>
        struct TextCheck : public std::false_type {};
        template <typename T>
        struct TextCheck<T,
        typename std::enable_if<std::is_same<std::string, T>::value ||
        std::is_same<const char *, T>::value>::type>
        : public std::true_type {};
        
        template <typename T, typename Enable = void>
        struct BLOBCheck : public std::false_type {};
        template <typename T>
        struct BLOBCheck<T,
        typename std::enable_if<std::is_same<void *, T>::value ||
        std::is_same<const void *, T>::value>::type>
        : public std::true_type {};
        
        /// null
        template <Type T = Type::null>
        struct TypeMeta {
            static constexpr const bool null_t      = true;
            static constexpr const bool float_t     = false;
            static constexpr const bool integer32_t = false;
            static constexpr const bool integer64_t = false;
            static constexpr const bool text_t      = false;
            static constexpr const bool blob_t      = false;
            static constexpr const bool default_t   = false;
            
            using CType = void;
            static constexpr const Type type = Type::null;
            static constexpr const char *sql_type = "";
        };
        template <typename T, typename Enable = void>
        struct Meta : public TypeMeta<Type::null> {};
        /// real
        template <>
        struct TypeMeta<Type::real> {
            static constexpr const bool null_t      = false;
            static constexpr const bool float_t     = true;
            static constexpr const bool integer32_t = false;
            static constexpr const bool integer64_t = false;
            static constexpr const bool text_t      = false;
            static constexpr const bool blob_t      = false;
            static constexpr const bool default_t   = true;
            
            using CType = double;
            static constexpr const Type type = Type::real;
            static constexpr const char *sql_type = "REAL";
        };
        template <typename T>
        struct Meta<T, typename std::enable_if<RealCheck<T>::value>::type>
        : public TypeMeta<Type::real> {};
        /// integer32
        template <>
        struct TypeMeta<Type::integer32> {
            static constexpr const bool null_t      = false;
            static constexpr const bool float_t     = false;
            static constexpr const bool integer32_t = true;
            static constexpr const bool integer64_t = false;
            static constexpr const bool text_t      = false;
            static constexpr const bool blob_t      = false;
            static constexpr const bool default_t   = true;
            
            using CType = int32_t;
            static constexpr const Type type = Type::integer32;
            static constexpr const char *sql_type = "INTEGER";
        };
        template <typename T>
        struct Meta<
        T,
        typename std::enable_if<Integer32Check<T>::value>::type>
        : public TypeMeta<Type::integer32> {};
        // integer64
        template <>
        struct TypeMeta<Type::integer64> {
            static constexpr const bool null_t      = false;
            static constexpr const bool float_t     = false;
            static constexpr const bool integer32_t = false;
            static constexpr const bool integer64_t = true;
            static constexpr const bool text_t      = false;
            static constexpr const bool blob_t      = false;
            static constexpr const bool default_t   = true;
            
            using CType = int64_t;
            static constexpr const Type type = Type::integer64;
            static constexpr const char *sql_type = "INTEGER";
        };
        template <typename T>
        struct Meta<
        T,
        typename std::enable_if<Integer64Check<T>::value>::type>
        : public TypeMeta<Type::integer64> {};
        /// text
        template <>
        struct TypeMeta<Type::text> {
            static constexpr const bool null_t      = false;
            static constexpr const bool float_t     = false;
            static constexpr const bool integer32_t = false;
            static constexpr const bool integer64_t = false;
            static constexpr const bool text_t      = true;
            static constexpr const bool blob_t      = false;
            static constexpr const bool default_t   = true;
            
            using CType = const char *;
            static constexpr const Type type = Type::text;
            static constexpr const char *sql_type = "TEXT";
        };
        template <typename T>
        struct Meta<T, typename std::enable_if<TextCheck<T>::value>::type>
        : public TypeMeta<Type::text> {};
        /// BLOB
        template <>
        struct TypeMeta<Type::blob> {
            static constexpr const bool null_t      = false;
            static constexpr const bool float_t     = false;
            static constexpr const bool integer32_t = false;
            static constexpr const bool integer64_t = false;
            static constexpr const bool text_t      = false;
            static constexpr const bool blob_t      = true;
            static constexpr const bool default_t   = false;
            
            using CType = const void *;
            using SizeType = int;
            static constexpr const Type type = Type::blob;
            static constexpr const char *sql_type = "BLOB";
        };
        template <typename T>
        struct Meta<T, typename std::enable_if<BLOBCheck<T>::value>::type>
        : public TypeMeta<Type::blob>{};
        
        static const std::string get_type(const Type type);
        
        ColumnDef(const Column & column, Type type);
        
        ColumnDef &primary(bool autoincrement = false, Order::Term order_term = Order::Term::none, Conflict conflict = Conflict::none);
        ColumnDef &not_null(Conflict conflict = Conflict::none);
        ColumnDef &unique(Conflict conflict = Conflict::none);
        ColumnDef &check(const Expr & expr);
        ColumnDef &ddefault(const char        *value);
        ColumnDef &ddefault(const std::string &value);
        ColumnDef &ddefault(const Expr &expr);
        ColumnDef &collate(const std::string &name);
        ColumnDef &collate(const char        *name);
        
        operator ColumnDefList() const;
    };
}

#endif /* column_def_hpp */

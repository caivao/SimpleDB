//
//  column_def.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "column_def.hpp"
#include "column.hpp"

namespace SDB {
    ColumnDef::ColumnDef(const Column & column, Type type)
    : Describable(column.name() + " " + ColumnDef::type(type))
    {}
    
    const std::string ColumnDef::type(const Type type)
    {
        switch (type) {
            case Type::real:  return TypeMeta<Type::real>::sql_type;
            case Type::int32: return TypeMeta<Type::int32>::sql_type;
            case Type::int64: return TypeMeta<Type::int64>::sql_type;
            case Type::text:  return TypeMeta<Type::text>::sql_type;
            case Type::blob:  return TypeMeta<Type::blob>::sql_type;
            default:          return TypeMeta<Type::null>::sql_type;
        }
    }
    
    ColumnDef::operator ColumnDefList(void) const
    {
        return {*this};
    }
    
    ColumnDef &ColumnDef::primary(bool autoincrement, Order::Term order_term, Conflict conflict)
    {
        _description.append(" PRIMARY KEY");
        if(order_term != Order::Term::none) {
            _description.append(" " + order_term.term());
        }
        if(conflict != Conflict::none) {
            _description.append(" ON CONFLICT " + conflict.conflict());
        }
        if(autoincrement) {
            _description.append(" AUTOINCREMENT");
        }
        return *this;
    }
    ColumnDef &ColumnDef::not_null(Conflict conflict)
    {
        _description.append(" NOT NULL");
        if(conflict != Conflict::none) {
            _description.append(" ON CONFLICT " + conflict.conflict());
        }
        return *this;
    }
    ColumnDef &ColumnDef::unique(Conflict conflict)
    {
        _description.append(" UNIQUE");
        if(conflict != Conflict::none) {
            _description.append(" ON CONFLICT " + conflict.conflict());
        }
        return *this;
    }
    ColumnDef &ColumnDef::check(const Expr & expr)
    {
        _description.append(" CHECK ( " + expr.description() + " )");
        return *this;
    }
    ColumnDef &ColumnDef::ddefault(const char        *value)
    {
        _description.append(" DEFAULT " + std::string(value));
        return *this;
    }
    ColumnDef &ColumnDef::ddefault(const std::string &value)
    {
        _description.append(" DEFAULT " + value);
        return *this;
    }
    ColumnDef &ColumnDef::ddefault(const Expr &expr)
    {
        _description.append(" DEFAULT ( " + expr.description() + " )");
        return *this;
    }
    ColumnDef &ColumnDef::collate(const char        *name)
    {
        _description.append(" COLLATE " + std::string(name));
        return *this;
    }
    ColumnDef &ColumnDef::collate(const std::string &name)
    {
        _description.append(" COLLATE " + name);
        return *this;
    }
}

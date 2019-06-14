//
//  expr.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyrhs © 2019 feng. All rhss reserved.
//

#include "expr.hpp"
#include "column.hpp"
#include "value_wrapper.hpp"

#define ExprFactory(...) Expr expr; expr._description.append(__VA_ARGS__); return expr;

namespace SDB {
    
    const Expr bind_parameter("?");
    
    Expr::Expr(void)
    : Describable("")
    {}
    
    Expr::Expr(const Column &column)
    : Describable(column.get_description())
    {}
    
    Expr::Expr(const char *value)
    : Describable(ValueWrapper(value))
    {}
    
    Expr::Expr(const std::string &value)
    : Describable(ValueWrapper(value))
    {}
    
    Expr::Expr(const std::nullptr_t &value)
    : Describable(ValueWrapper(value))
    {}
    
    Expr::Expr(const void *value, int size)
    : Describable(ValueWrapper(value, size))
    {}
    
    Expr::operator ExprList(void) const
    {
        return {*this};
    }
    
    Expr Expr::operator !(void) const
    {
        ExprFactory("NOT (" + _description + ")");
    }
    
    Expr Expr::operator +(void) const
    {
        ExprFactory("(" + _description + ")")
    }
    
    Expr Expr::operator -(void) const
    {
        ExprFactory("-(" + _description + ")");
    }
    
    Expr Expr::operator ~(void) const
    {
        ExprFactory("~(" + _description + ")");
    }
    
    Expr Expr::operator ||(const Expr &operand) const
    {
        ExprFactory("(" + _description + " OR " + operand._description + ")");
    }
    
    Expr Expr::operator &&(const Expr &operand) const
    {
        ExprFactory("(" + _description + " AND " + operand._description + ")");
    }
    
    Expr Expr::operator  +(const Expr &operand) const
    {
        ExprFactory("(" + _description + " + " + operand._description + ")");
    }
    
    Expr Expr::operator  -(const Expr &operand) const
    {
        ExprFactory("(" + _description + " - " + operand._description + ")");
    }
    
    Expr Expr::operator  *(const Expr &operand) const
    {
        ExprFactory("(" + _description + " * " + operand._description + ")");
    }
    
    Expr Expr::operator  /(const Expr &operand) const
    {
        ExprFactory("(" + _description + " / " + operand._description + ")");
    }
    
    Expr Expr::operator  %(const Expr &operand) const
    {
        ExprFactory("(" + _description + " % " + operand._description + ")");
    }
    
    Expr Expr::operator <<(const Expr &operand) const
    {
        ExprFactory("(" + _description + " << " + operand._description + ")");
    }
    
    Expr Expr::operator >>(const Expr &operand) const
    {
        ExprFactory("(" + _description + " >> " + operand._description + ")");
    }
    
    Expr Expr::operator  &(const Expr &operand) const
    {
        ExprFactory("(" + _description + " & " + operand._description + ")");
    }
    
    Expr Expr::operator  |(const Expr &operand) const
    {
        ExprFactory("(" + _description + " | " + operand._description + ")");
    }
    
    Expr Expr::operator  <(const Expr &operand) const
    {
        ExprFactory("(" + _description + " < " + operand._description + ")");
    }
    
    Expr Expr::operator <=(const Expr &operand) const
    {
        ExprFactory("(" + _description + " <= " + operand._description + ")");
    }
    
    Expr Expr::operator  >(const Expr &operand) const
    {
        ExprFactory("(" + _description + " > " + operand._description + ")");
    }
    
    Expr Expr::operator >=(const Expr &operand) const
    {
        ExprFactory("(" + _description + " >= " + operand._description + ")");
    }
    
    Expr Expr::operator ==(const Expr &operand) const
    {
        ExprFactory("(" + _description + " = " + operand._description + ")");
    }
    
    Expr Expr::operator !=(const Expr &operand) const
    {
        ExprFactory("(" + _description + " != " + operand._description + ")");
    }
    
    Expr Expr::concat(const Expr &operand) const
    {
        ExprFactory("(" + _description + "||" + operand._description + ")");
    }
    
    Expr Expr::substr(const Expr &start, const Expr &length) const
    {
        ExprFactory("SUBSTR(" + _description + "," + start._description + "," + length._description + ")");
    }
    
    Expr Expr::in(const std::string &table) const
    {
        ExprFactory("(" + _description + " IN " + table + ")");
    }
    
    Expr Expr::between(const Expr &lhs, const Expr &rhs) const
    {
        ExprFactory("(" + _description + " BETWEEN " + lhs._description + " AND " + rhs._description + ")");
    }
    
    Expr Expr::like(const Expr &operand) const
    {
        ExprFactory("(" + _description + " LIKE " + operand._description + ")");
    }
    
    Expr Expr::glob(const Expr &operand) const
    {
        ExprFactory("(" + _description + " GLOB " + operand._description + ")");
    }
    
    Expr Expr::match(const Expr &operand) const
    {
        ExprFactory("(" + _description + " MATCH " + operand._description + ")");
    }
    
    Expr Expr::regexp(const Expr &operand) const
    {
        ExprFactory("(" + _description + " REGEXP" + operand._description + ")");
    }
    
    Expr Expr::like(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " LIKE" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::glob(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " GLOB" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::match(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " MATCH" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::regexp(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " REGEXP" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::is_null(void) const
    {
        ExprFactory("(" + _description + " ISNULL" + ")");
    }
    
    Expr Expr::is(const Expr &operand) const
    {
        ExprFactory("(" + _description + " IS " + operand._description + ")");
    }
    
    Expr Expr::not_between(const Expr &lhs, const Expr &rhs) const
    {
        ExprFactory("(" + _description + " NOT BETWEEN " + lhs._description + " AND " + rhs._description + ")");
    }
    
    Expr Expr::not_in(const std::string &table) const
    {
        ExprFactory("(" + _description + " NOT IN " + table + ")");
    }
    
    Expr Expr::not_like(const Expr &operand) const
    {
        ExprFactory("(" + _description + " NOT LIKE " + operand._description + ")");
    }
    
    Expr Expr::not_glob(const Expr &operand) const
    {
        ExprFactory("(" + _description + " NOT GLOB " + operand._description + ")");
    }
    
    Expr Expr::not_match(const Expr &operand) const
    {
        ExprFactory("(" + _description + " NOT MATCH " + operand._description + ")");
    }
    
    Expr Expr::not_regexp(const Expr &operand) const
    {
        ExprFactory("(" + _description + " NOT REGEXP" + operand._description + ")");
    }
    
    Expr Expr::not_like(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " NOT LIKE" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::not_glob(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " NOT GLOB" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::not_match(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " NOT MATCH" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::not_regexp(const Expr &operand, const Expr &escape) const
    {
        ExprFactory("(" + _description + " NOT REGEXP" + operand._description + " ESCAPE " + escape._description + ")");
    }
    
    Expr Expr::is_not_null() const
    {
        ExprFactory("(" + _description + " NOTNULL" + ")");
    }
    
    Expr Expr::is_not(const Expr &operand) const
    {
        ExprFactory("(" + _description + " IS NOT " + operand._description + ")");
    }
    
    Expr Expr::avg(bool distinct) const
    {
        return Expr::functionn("AVG", {*this}, distinct);
    }
    
    Expr Expr::count(bool distinct) const
    {
        return Expr::functionn("COUNT", {*this}, distinct);
    }
    
    Expr Expr::max(bool distinct) const
    {
        return Expr::functionn("MAX", {*this}, distinct);
    }
    
    Expr Expr::min(bool distinct) const
    {
        return Expr::functionn("MIN", {*this}, distinct);
    }
    
    Expr Expr::sum(bool distinct) const
    {
        return Expr::functionn("SUM", {*this}, distinct);
    }
    
    Expr Expr::total(bool distinct) const
    {
        return Expr::functionn("TOTAL", {*this}, distinct);
    }
    
    Expr Expr::abs(bool distinct) const
    {
        return Expr::functionn("ABS", {*this}, distinct);
    }
    
    Expr Expr::hex(bool distinct) const
    {
        return Expr::functionn("HEX", {*this}, distinct);
    }
    
    Expr Expr::length(bool distinct) const
    {
        return Expr::functionn("LENGTH", {*this}, distinct);
    }
    
    Expr Expr::lower(bool distinct) const
    {
        return Expr::functionn("LOWER", {*this}, distinct);
    }
    
    Expr Expr::upper(bool distinct) const
    {
        return Expr::functionn("UPPER", {*this}, distinct);
    }
    
    Expr Expr::round(bool distinct) const
    {
        return Expr::functionn("ROUND", {*this}, distinct);
    }
}



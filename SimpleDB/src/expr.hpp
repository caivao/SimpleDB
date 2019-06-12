//
//  expr.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef expr_hpp
#define expr_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    class Expr: public Describable {
    public:
        static const Expr bind_parameter;
        
        Expr();
        Expr(const Column &column);
        Expr(const char *value);
        Expr(const std::string &value);
        Expr(const std::nullptr_t &value);
        Expr(const void *value, int size);
        
        operator ExprList() const;
        
        Expr operator !(void) const;
        Expr operator +(void) const;
        Expr operator -(void) const;
        Expr operator ~(void) const;
        
        Expr operator ||(const Expr &operand) const;
        Expr operator &&(const Expr &operand) const;
        
        Expr operator  +(const Expr &operand) const;
        Expr operator  -(const Expr &operand) const;
        Expr operator  *(const Expr &operand) const;
        Expr operator  /(const Expr &operand) const;
        Expr operator  %(const Expr &operand) const;
        
        Expr operator <<(const Expr &operand) const;
        Expr operator >>(const Expr &operand) const;
        
        Expr operator  &(const Expr &operand) const;
        Expr operator  |(const Expr &operand) const;
        
        Expr operator  <(const Expr &operand) const;
        Expr operator <=(const Expr &operand) const;
        Expr operator  >(const Expr &operand) const;
        Expr operator >=(const Expr &operand) const;
        
        Expr operator ==(const Expr &operand) const;
        Expr operator !=(const Expr &operand) const;
        
        Expr concat(const Expr &operand) const;
        Expr substr(const Expr &start, const Expr &length) const;
        
        template <typename T = Expr>
        typename std::enable_if<std::is_base_of<Expr, T>::value,
        Expr>::type
        in(const std::list<const T> & expr_list) const
        {
            Expr expr;
            expr._description.append(_description + " IN(");
            expr.component_join(expr_list);
            expr._description.append(")");
            return expr;
        }
        Expr in     (const std::string &table) const;
        Expr between(const Expr &left, const Expr &right) const;
        
        Expr like  (const Expr &operand) const;
        Expr glob  (const Expr &operand) const;
        Expr match (const Expr &operand) const;
        Expr regexp(const Expr &operand) const;
        
        Expr like  (const Expr &operand, const Expr &escape) const;
        Expr glob  (const Expr &operand, const Expr &escape) const;
        Expr match (const Expr &operand, const Expr &escape) const;
        Expr regexp(const Expr &operand, const Expr &escape) const;
        
        Expr is_null(void) const;
        Expr is     (const Expr &operand) const;
        
        template <typename T = Expr>
        typename std::enable_if<std::is_base_of<Expr, T>::value,
        Expr>::type
        not_in(const std::list<const T> &expr_list) const
        {
            Expr expr;
            expr._description.append(_description + " NOT IN(");
            expr.component_join(expr_list);
            expr._description.append(")");
            return expr;
        }
        Expr not_in     (const std::string &table) const;
        Expr not_between(const Expr &lhs, const Expr &rhs) const;

        Expr not_like  (const Expr &operand) const;
        Expr not_glob  (const Expr &operand) const;
        Expr not_match (const Expr &operand) const;
        Expr not_regexp(const Expr &operand) const;
        
        Expr not_like  (const Expr &operand, const Expr &escape) const;
        Expr not_glob  (const Expr &operand, const Expr &escape) const;
        Expr not_match (const Expr &operand, const Expr &escape) const;
        Expr not_regexp(const Expr &operand, const Expr &escape) const;
        
        Expr is_not_null(void) const;
        Expr is_not(const Expr &operand) const;
        
        template <typename T = Expr>
        static typename std::enable_if<std::is_base_of<Expr, T>::value,
        Expr>::type
        combine(const std::list<const T> &expr_list)
        {
            Expr expr;
            expr._description.append("(");
            expr.component_join(expr_list);
            expr._description.append(")");
            return expr;
        }
        
        Expr avg(bool distinct = false) const;
        Expr count(bool distinct = false) const;
        Expr max(bool distinct = false) const;
        Expr min(bool distinct = false) const;
        Expr sum(bool distinct = false) const;
        Expr total(bool distinct = false) const;
        
        Expr abs(bool distinct = false) const;
        Expr hex(bool distinct = false) const;
        Expr length(bool distinct = false) const;
        Expr lower(bool distinct = false) const;
        Expr upper(bool distinct = false) const;
        Expr round(bool distinct = false) const;
        
        template <typename T = Expr>
        static typename std::enable_if<std::is_base_of<Expr, T>::value,
        Expr>::type
        ffunction(const std::string &function,
                  const std::list<const T> &expr_list,
                  bool distinct = false)
        {
            Expr expr;
            expr._description.append(function + "(");
            if (distinct) {
                expr._description.append("DISTINCT ");
            }
            expr.component_join(expr_list);
            expr._description.append(")");
            return expr;
        }
    };
}

#endif /* expr_hpp */

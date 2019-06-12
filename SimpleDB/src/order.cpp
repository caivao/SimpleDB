//
//  order.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "order.hpp"
#include "expr.hpp"

namespace SDB {
    Order::Order(const Expr &expr, const std::string &collation, Term term)
    : Describable(expr.get_description())
    {
        if (!collation.empty()) {
            _description.append(" ");
            _description.append(collation);
        }
        if (term != Term::none) {
            _description.append(" ");
            _description.append(term.get_term());
        }
    }
    
    Order::Order(const Expr &expr, Term term)
    : Describable(expr.get_description())
    {
        if(term != Term::none) {
            _description.append(" ");
            _description.append(term.get_term());
        }
    }
    
    Order::operator OrderList() const
    {
        return {*this};
    }
    
    const Order::Term &Order::Term::none(Term::Type::none);
    const Order::Term &Order::Term::asc(Term::Type::asc);
    const Order::Term &Order::Term::desc(Term::Type::desc);
    
    const std::string &Order::Term::get_term(void) const
    {
        return _description;
    }
    
    bool Order::Term::operator !=(const Term & operand) const
    {
        return type != operand.type;
    }
    bool Order::Term::operator ==(const Term & operand) const
    {
        return type == operand.type;
    }
    
    Order::Term::Term(const Type type)
    : Describable(""), type(type)
    {
        switch (type) {
            case Type::asc:
                _description.append("ASC");
                break;
            case Type::desc:
                _description.append("DESC");
                break;
            default:
                break;
        }
    }
}
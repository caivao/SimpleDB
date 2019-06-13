//
//  column_index.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "column_index.hpp"
#include "column.hpp"
#include "expr.hpp"

namespace SDB {
    ColumnIndex::ColumnIndex(const Column &column, const Order::Term &term)
    : Describable(column.get_name())
    {
        if (term != Order::Term::none) {
            _description.append(" ");
            _description.append(term.get_term());
        }
    }
    
    ColumnIndex::ColumnIndex(const Expr &expr, const Order::Term &term)
    : Describable(expr.get_description())
    {
        if (term != Order::Term::none) {
            _description.append(" ");
            _description.append(term.get_term());
        }
    }
    
    ColumnIndex::operator ColumnIndexList() const
    {
        return {*this};
    }
}
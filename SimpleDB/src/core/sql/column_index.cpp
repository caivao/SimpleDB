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
    : Describable(column.name())
    {
        if (term != Order::Term::none) {
            _description.append(" ");
            _description.append(term.term());
        }
    }
    
    ColumnIndex::ColumnIndex(const Expr &expr, const Order::Term &term)
    : Describable(expr.description())
    {
        if (term != Order::Term::none) {
            _description.append(" ");
            _description.append(term.term());
        }
    }
    
    ColumnIndex::operator ColumnIndexList(void) const
    {
        return {*this};
    }
}

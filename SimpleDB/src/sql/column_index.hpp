//
//  column_index.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef column_index_hpp
#define column_index_hpp

#include "declare.hpp"
#include "describable.hpp"
#include "order.hpp"

namespace SDB {
    class ColumnIndex : public Describable {
    public:
        ColumnIndex(const Column &column, const Order::Term &term = Order::Term::none);
        ColumnIndex(const Expr &expr, const Order::Term &term = Order::Term::none);
        
        operator ColumnIndexList() const;
    };
}

#endif /* column_index_hpp */

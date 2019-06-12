//
//  declare.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef declare_hpp
#define declare_hpp

#include <atomic>
#include <cassert>
#include <functional>
#include <list>
#include <string>
#include <utility>

namespace SDB {
    class Describable;
    class Column;
    class ColumnDef;
    class ColumnIndex;
    class Expr;
    class Order;
    class Pragma;
    class ValueWrapper;
    class NestedQuery;
    class Join;
    
    namespace STMT {
        class Statement;
        class CreateTable;
        class DropTable;
        class AlterTable;
        class CreateIndex;
        class DropIndex;
        class Insert;
        class Delete;
        class Update;
        class Select;
        class Pragma;
        class Vacuum;
        class Rollback;
        class SavePoint;
    }
    
    typedef std::list<const Expr> ExprList;
    typedef std::list<const Column> ColumnList;
    typedef std::list<const ColumnDef> ColumnDefList;
    typedef std::list<const ColumnIndex> ColumnIndexList;
    typedef std::list<const Order> OrderList;
    typedef std::list<const NestedQuery> NestedQueryList;
}

#endif /* declare_hpp */
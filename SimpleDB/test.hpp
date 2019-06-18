//
//  test.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/18.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef test_hpp
#define test_hpp

#include "declare.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include "action.hpp"

using namespace SDB;
using namespace STMT;
using namespace std;

namespace SDB {
    class SubExpr : public Expr {
    public:
        SubExpr(void)
        : Expr("")
        {}
        
        SubExpr(const Column &column)
        : Expr(column)
        {}
        
        SubExpr(const char *value)
        : Expr(value)
        {}
        
        SubExpr(const std::string &value)
        : Expr(value)
        {}
        
        SubExpr(const std::nullptr_t &value)
        : Expr(value)
        {}
        
        SubExpr(const void *value, int size)
        : Expr(value, size)
        {}
    };
}

#endif /* test_hpp */

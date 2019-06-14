//
//  main.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/4.
//  Copyright © 2019 feng. All rights reserved.
//

#include <iostream>

#include "declare.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include "action.hpp"

using namespace SDB;
using namespace STMT;
using namespace std;

int main(int argc, const char * argv[]) {
    std::cout << "+++++++++++" << std::endl;
    STMT::Select().select({ Column("name") }).from("sqlite_master").where((Expr(Column("type")) == "table") && (Expr(Column("name")) == "table")).limit(1).print();
    Insert().insert("student").print();
    Select().select({"name", "age"}).from("student").where(SDB::Expr(SDB::Column("name")) == "lifeng").print();
    Vacuum().vacuum("hahaha").print();
    Expr(SDB::Column("ccc").at("Table")).not_like("nihao").print();
    (STMT::Pragma().pragma(SDB::Pragma::auto_vacuum) = true).print();
    std::cout << "-----------" << std::endl;
    return 0;
}

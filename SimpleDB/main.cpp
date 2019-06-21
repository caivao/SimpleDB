//
//  main.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/4.
//  Copyright © 2019 feng. All rights reserved.
//

#include <iostream>

#include "SDB.h"
#include "test.hpp"

using namespace SDB;
using namespace STMT;
using namespace std;

int main(int argc, const char * argv[]) {
    cout << "+++++++++++" << endl;
    STMT::Select().select({ Column("name") }).from("sqlite_master").where((Expr(Column("type")) == "table") && (Expr(Column("name")) == "table")).limit(1).print();
    Insert().insert("student").print();
    Select().select({"name", "age"}).from("student").where(Expr(Column("name")) == "lifeng").print();
    Vacuum().vacuum("hahaha").print();
    Expr(Column("ccc").at("Table")).not_like("nihao").print();
    (STMT::Pragma().pragma(SDB::Pragma::auto_vacuum) = true).print();
    cout << "-----------" << endl;
    return 0;
}

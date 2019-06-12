//
//  main.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/4.
//  Copyright © 2019 feng. All rights reserved.
//

#include <iostream>

#include "declare.hpp"
#include "describable.hpp"
#include "statement.hpp"
#include "Expr.hpp"
#include "column.hpp"
#include "statement_vacuum.hpp"
#include "statement_select.hpp"
#include "statement_insert.hpp"
#include "statement_pragma.hpp"
#include "statement_create_table.hpp"

template <typename T = SDB::STMT::Statement>
typename std::enable_if<std::is_base_of<SDB::STMT::Statement, T>::value,
void >::type
print(const T &test) {
    test.print();
}

int main(int argc, const char * argv[]) {
    std::cout << "+++++++++++" << std::endl;
    SDB::STMT::Insert().insert("student").print();
    SDB::STMT::Select().select({"name", "age"}).from("student").where(SDB::Expr(SDB::Column("name")) == "lifeng").print();
    SDB::STMT::Vacuum().vacuum("hahaha").print();
    SDB::Expr(SDB::Column("ccc").in_table("Table")).not_like("nihao").print();
    (SDB::STMT::Pragma().pragma(SDB::Pragma::auto_vacuum) = true).print();
    print(SDB::STMT::CreateTable().create("表明"));
    std::cout << "-----------" << std::endl;
    return 0;
}

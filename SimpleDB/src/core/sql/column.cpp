//
//  column.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "column.hpp"

namespace SDB {
    const Column Column::all("*");
    const Column Column::rowid("rowid");
    
    Column::Column(void)
    : Describable("")
    {}
    
    Column::Column(const char *name)
    : Describable(name)
    {}
    
    Column::Column(const std::string &name)
    : Describable(name)
    {}
    
    const std::string &Column::name(void) const
    {
        return _description;
    }
    
    Column Column::at(const std::string &table) const
    {
        return Column(table + "." + _description);
    }
    
    Column &Column::as(const std::string & alias)
    {
        _description.append("AS " + alias);
        return *this;
    }
    
    Column::operator ColumnList(void) const
    {
        return {*this};
    }
    
    bool Column::operator ==(const Column &column) const
    {
        return _description == column._description;
    }
    bool Column::operator !=(const Column &column) const
    {
        return _description != column._description;
    }
}

//
//  conflict.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#include "conflict.hpp"

namespace SDB {
    
    const Conflict &Conflict::none(Type::none);
    const Conflict &Conflict::rollback(Type::rollback);
    const Conflict &Conflict::abort(Type::abort);
    const Conflict &Conflict::fail(Type::fail);
    const Conflict &Conflict::ignore(Type::ignore);
    const Conflict &Conflict::replace(Type::replace);
    
    Conflict::Conflict(const Type type): Describable(""), type(type)
    {
        switch (type) {
            case Type::rollback:
                _description.append("ROLLBACK");
                break;
            case Type::abort:
                _description.append("ABORT");
                break;
            case Type::fail:
                _description.append("FAIL");
                break;
            case Type::ignore:
                _description.append("IGNORE");
                break;
            case Type::replace:
                _description.append("REPLACE");
                break;
            default:
                break;
        }
    }
    
    const std::string &Conflict::get_conflict(void) const
    {
        return _description;
    }
    
    bool Conflict::operator !=(const Conflict & operand) const
    {
        return type != operand.type;
    }
    bool Conflict::operator ==(const Conflict & operand) const
    {
        return type == operand.type;
    }
}

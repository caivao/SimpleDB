//
//  statement_releasable.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "statement_releasable.hpp"

namespace SDB {
    
    StatementReleasable::StatementReleasable(const HandleReleasable &handle, const std::shared_ptr<ValueBinder> &binder)
    : _handle(handle), _binder(binder)
    {}
    
    StatementReleasable::StatementReleasable(void)
    : _binder(nullptr), _handle({nullptr, nullptr})
    {}
    
    StatementReleasable::operator bool(void) const
    {
        return _binder != nullptr;
    }
    
    bool StatementReleasable::operator!=(const std::nullptr_t &) const
    {
        return _binder != nullptr;
    }
    
    bool StatementReleasable::operator==(const std::nullptr_t &) const
    {
        return _binder == nullptr;
    }
    
    StatementReleasable &StatementReleasable::operator=(const std::nullptr_t &)
    {
        _binder = nullptr;
        _handle = nullptr;
        return *this;
    }
    
}

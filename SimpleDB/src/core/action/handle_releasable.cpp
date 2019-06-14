//
//  handle_releasable.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "handle_releasable.hpp"

namespace SDB {
    
    HandleWrapper::HandleWrapper(const std::shared_ptr<Handle> &handle, const Configure &configure)
    : handle(handle), configure(configure)
    {}
    
    HandleReleasable::HandleReleasable(const std::shared_ptr<HandleWrapper> &value, const Releasable<std::shared_ptr<HandleWrapper>>::OnReleased &on_released)
    : _value(value), _releasable(value, on_released)
    {}
    
    HandleReleasable::operator bool() const
    {
        return _value != nullptr;
    }
    
    bool HandleReleasable::operator!=(const std::nullptr_t &) const
    {
        return _value != nullptr;
    }
    
    bool HandleReleasable::operator==(const std::nullptr_t &) const
    {
        return _value == nullptr;
    }
    
    HandleReleasable &HandleReleasable::operator=(const std::nullptr_t &)
    {
        _value = nullptr;
        _releasable = nullptr;
        return *this;
    }
    
}

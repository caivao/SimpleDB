//
//  handle_releasable.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef handle_releasable_hpp
#define handle_releasable_hpp

#include "declare.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include "configure.hpp"

namespace SDB {
    
    class HandleWrapper {
    public:
        HandleWrapper(const std::shared_ptr<Handle> &handle, const Configure &configure);
        
        constexpr Handle *operator->(void) const { return handle.get(); }
        
        std::shared_ptr<Handle> handle;
        Configure configure;
    };
    
    class HandleReleasable {
    public:
        HandleReleasable(const std::shared_ptr<HandleWrapper> &value, const Releasable<std::shared_ptr<HandleWrapper>>::OnReleased &onReleased);
        constexpr Handle *operator->(void) const {
            return _value->operator->();
        }
        operator bool(void) const;
        bool operator!=(const std::nullptr_t &) const;
        bool operator==(const std::nullptr_t &) const;
        
        HandleReleasable &operator=(const std::nullptr_t &);
        
    protected:
        std::shared_ptr<HandleWrapper> _value;
        Releasable<std::shared_ptr<HandleWrapper>> _releasable;
    };
}

#endif /* handle_releasable_hpp */

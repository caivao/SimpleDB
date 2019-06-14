//
//  statement_releasable.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_releasable_hpp
#define statement_releasable_hpp

#include "declare.hpp"
#include "sql.hpp"
#include "handle_releasable.hpp"

namespace SDB {
    class StatementReleasable {
    public:
        StatementReleasable(const HandleReleasable &handle, const std::shared_ptr<ValueBinder> &binder);
        constexpr ValueBinder *operator->() const
        {
            return _binder.get();
        }
        StatementReleasable();
        operator bool() const;
        bool operator!=(const std::nullptr_t &) const;
        bool operator==(const std::nullptr_t &) const;
        StatementReleasable &operator=(const std::nullptr_t &);
        
    protected:
        HandleReleasable _handle;
        std::shared_ptr<ValueBinder> _binder;
    };
}

#endif /* statement_releasable_hpp */

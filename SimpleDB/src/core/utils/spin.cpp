//
//  spin.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "spin.hpp"

namespace SDB {
    
    void Spin::lock(void)
    {
        while (_locked.test_and_set(std::memory_order_acquire))
            ;
    }
    
    void Spin::unlock(void)
    {
        _locked.clear(std::memory_order_release);
    }
    
}

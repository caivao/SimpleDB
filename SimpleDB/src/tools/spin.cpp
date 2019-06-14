//
//  spin.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "spin.hpp"

namespace SDB {
    
    void Spin::lock()
    {
        while (locked.test_and_set(std::memory_order_acquire))
            ;
    }
    
    void Spin::unlock()
    {
        locked.clear(std::memory_order_release);
    }
    
}

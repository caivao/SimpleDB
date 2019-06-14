//
//  spin.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef spin_hpp
#define spin_hpp

#include <atomic>

namespace SDB {
    
    class Spin {
    public:
        void lock();
        void unlock();
        
    protected:
        std::atomic_flag locked = ATOMIC_FLAG_INIT;
    };
    
    template <typename Spin>
    class SpinLockGuard {
    public:
        SpinLockGuard(Spin &spin) : _spin(spin)
        {
            _spin.lock();
        }
        
        ~SpinLockGuard()
        {
            _spin.unlock();
        }
        
    protected:
        Spin &_spin;
    };
    
}

#endif /* spin_hpp */

//
//  spin.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef spin_hpp
#define spin_hpp

#include <atomic>

namespace SDB {
    
    class Spin {
    public:
        void lock(void);
        void unlock(void);
        
    protected:
        std::atomic_flag _locked = ATOMIC_FLAG_INIT;
    };
    
    template <typename Spin>
    class SpinLockGuard {
    public:
        SpinLockGuard(Spin &spin) : _spin(spin)
        {
            _spin.lock();
        }
        
        ~SpinLockGuard(void)
        {
            _spin.unlock();
        }
        
    protected:
        Spin &_spin;
    };
    
}

#endif /* spin_hpp */

//
//  rwlock.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef rwlock_hpp
#define rwlock_hpp

#include <condition_variable>
#include <mutex>

//std::shared_lock is supported from C++14

namespace SDB {
    
    class RWlock {
    public:
        RWlock(void);
        ~RWlock(void);
        void lock_read(void);
        void unlock_read(void);
        bool try_lock_read(void);
        
        void lock_write(void);
        void unlock_write(void);
        bool try_lock_write(void);
        
        bool is_writing(void) const;
        bool is_reading(void) const;
        
    protected:
        mutable std::mutex _mutex;
        std::condition_variable _cond;
        int _reader;
        int _writer;
        int _pending;
    };
    
}

#endif /* rwlock_hpp */

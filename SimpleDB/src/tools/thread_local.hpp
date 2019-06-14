//
//  thread_local.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef thread_local_hpp
#define thread_local_hpp

#include <pthread.h>

namespace SDB {
    
    template <typename T>
    class ThreadLocal {
    public:
        ThreadLocal()
        : _default_value(nullptr)
        {
            pthread_key_create(&_key, [](void *value) { delete (T *) value; });
        }
        
        ThreadLocal(const T &default_value)
        : _default_value(new T(default_value))
        {
            pthread_key_create(&_key, [](void *value) { delete (T *) value; });
        }
        
        T *get()
        {
            T *value = (T *) pthread_getspecific(_key);
            if (value) {
                return value;
            }
            value = new T;
            if (_default_value) {
                *value = *_default_value;
            }
            pthread_setspecific(_key, value);
            return value;
        }
        
        ~ThreadLocal()
        {
            if (_default_value) {
                delete _default_value;
                _default_value = nullptr;
            }
            pthread_key_delete(_key);
        }
        
    protected:
        pthread_key_t _key;
        T *_default_value;
    };
    
}

#endif /* thread_local_hpp */

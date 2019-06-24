//
//  thread_share.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef thread_share_hpp
#define thread_share_hpp

#include <pthread.h>

namespace SDB {
    
    /// 同线程下不同方法（函数）间数据共享
    template <typename T>
    class ThreadShare {
    public:
        ThreadShare(void)
        : _value(nullptr)
        {
            /// 创建 pthread_key_t 变量， 第二个参数在线程释放的时候清理操作
            pthread_key_create(&_key, [](void *value) { delete (T *) value; });
        }
        
        ThreadShare(const T &value)
        : _value(new T(value))
        {
            /// 创建 pthread_key_t 变量， 第二个参数在线程释放的时候清理操作
            pthread_key_create(&_key, [](void *value) { delete (T *) value; });
        }
        
        T *get(void)
        {
            /// 同一线程间不同函数的数据共享 -> 取值
            T *value = (T *) pthread_getspecific(_key);
            if (value) {
                return value;
            }
            value = new T;
            if (_value) {
                *value = *_value;
            }
            /// 同一线程间不同函数的数据共享 -> 赋值
            pthread_setspecific(_key, value);
            return value;
        }
        
        ~ThreadShare(void)
        {
            if (_value) {
                delete _value;
                _value = nullptr;
            }
            pthread_key_delete(_key);
        }
        
    protected:
        pthread_key_t _key;
        T *_value;
    };
    
}

#endif /* thread_share_hpp */

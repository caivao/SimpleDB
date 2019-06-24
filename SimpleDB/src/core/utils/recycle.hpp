//
//  recycle.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef recycle_hpp
#define recycle_hpp

#include "declare.hpp"
#include <functional>

namespace SDB {
    
    template <typename T>
    class Recycle {
    public:
        typedef std::function<void(T &)> OnRecycled;
        static const Recycle invalid;
        
        Recycle(const T &value, const OnRecycled &on_recycled)
        : _value(value)
        , _on_recycled(on_recycled)
        , _reference(new std::atomic<int>(1))
        {}
        
        Recycle(const Recycle &other)
        : _value(other._value)
        , _on_recycled(other._on_recycled)
        , _reference(other._reference)
        {
            retain();
        }
        
        Recycle &operator=(const Recycle &other)
        {
            other.retain();
            release();
            _value = other._value;
            _on_recycled = other._on_recycled;
            _reference = other._reference;
            return *this;
        }
        
        typename std::enable_if<std::is_convertible<std::nullptr_t, T>::value,
        Recycle &>::type
        operator=(const std::nullptr_t &)
        {
            release();
        _value = nullptr;
            _reference = nullptr;
            _on_recycled = nullptr;
            return *this;
        }
        
        ~Recycle(void)
        {
            release();
        }
        
        constexpr T operator->(void) const
        {
            return _value;
        }
        
        typename std::enable_if<std::is_convertible<std::nullptr_t, T>::value,
        bool>::type
        operator!=(const std::nullptr_t &) const
        {
            return _value != nullptr;
        }
        
        typename std::enable_if<std::is_convertible<std::nullptr_t, T>::value,
        bool>::type
        operator==(const std::nullptr_t &) const
        {
            return _value == nullptr;
        }
        
    protected:
        Recycle(void) //invalid
        : _reference(new std::atomic<int>(0))
        {}
        
        void retain(void) const
        {
            if (_reference) {
                ++(*_reference);
            }
        }
        
        void release()
        {
            if (_reference) {
                if (--(*_reference) == 0) {
                    delete _reference;
                    _reference = nullptr;
                    if (_on_recycled) {
                        _on_recycled(_value);
                        _on_recycled = nullptr;
                    }
                }
            }
        }
        
        T _value;
        mutable std::atomic<int> *_reference;
        Recycle::OnRecycled _on_recycled;
    };
    
}

#endif /* recycle_hpp */

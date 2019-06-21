//
//  releasable.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef releasable_hpp
#define releasable_hpp

#include "declare.hpp"
#include <functional>

namespace SDB {
    
    template <typename T>
    class Releasable {
    public:
        typedef std::function<void(T &)> OnReleased;
        static const Releasable invalid;
        
        Releasable(const T &value, const OnReleased &on_released)
        : _value(value)
        , _on_released(on_released)
        , _reference(new std::atomic<int>(1))
        {}
        
        Releasable(const Releasable &other)
        : _value(other._value)
        , _on_released(other._on_released)
        , _reference(other._reference)
        {
            retain();
        }
        
        Releasable &operator=(const Releasable &other)
        {
            other.retain();
            release();
            _value = other._value;
            _on_released = other._on_released;
            _reference = other._reference;
            return *this;
        }
        
        typename std::enable_if<std::is_convertible<std::nullptr_t, T>::value,
        Releasable &>::type
        operator=(const std::nullptr_t &)
        {
            release();
            _value = nullptr;
            _reference = nullptr;
            _on_released = nullptr;
            return *this;
        }
        
        ~Releasable(void)
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
        Releasable(void) //invalid
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
                    if (_on_released) {
                        _on_released(_value);
                        _on_released = nullptr;
                    }
                }
            }
        }
        
        T _value;
        mutable std::atomic<int> *_reference;
        Releasable::OnReleased _on_released;
    };
    
}

#endif /* releasable_hpp */

//
//  concurrent_list.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef concurrent_list_hpp
#define concurrent_list_hpp

#include "spin.hpp"
#include <list>

namespace SDB {
    
    template <typename T>
    class ConcurrentList {
    public:
        using ElementType = std::shared_ptr<T>;
        ConcurrentList(size_t capacity_cap)
        : _capacity_cap(capacity_cap)
        {}
        
        size_t capacity_cap(void) const
        {
            SpinLockGuard<Spin> lockGuard(_spin);
            return _capacity_cap;
        }
        
        bool push_back(const ElementType &value)
        {
            SpinLockGuard<Spin> lockGuard(_spin);
            if (_list.size() < _capacity_cap) {
                _list.push_back(value);
                return true;
            }
            return false;
        }
        
        bool push_front(const ElementType &value)
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            if (_list.size() < _capacity_cap) {
                _list.push_front(value);
                return true;
            }
            return false;
        }
        
        ElementType pop_back(void)
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            if (_list.empty()) {
                return nullptr;
            }
            ElementType value = _list.back();
            _list.pop_back();
            return value;
        }
        
        ElementType pop_front(void)
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            if (_list.empty()) {
                return nullptr;
            }
            ElementType value = _list.front();
            _list.pop_front();
            return value;
        }
        
        bool empty(void) const
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            return _list.empty();
        }
        
        size_t size(void) const
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            return _list.size();
        }
        
        size_t clear(void)
        {
            SpinLockGuard<Spin> lock_guard(_spin);
            size_t size = _list.size();
            _list.clear();
            return size;
        }
        
    protected:
        std::list<ElementType> _list;
        size_t _capacity_cap;
        mutable Spin _spin;
    };
    
}

#endif /* concurrent_list_hpp */

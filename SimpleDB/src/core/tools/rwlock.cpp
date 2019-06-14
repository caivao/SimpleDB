//
//  rwlock.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "rwlock.hpp"

namespace SDB {
    
    RWlock::RWlock()
    : _reader(0), _writer(0), _pending(0)
    {}
    
    RWlock::~RWlock()
    {}
    
    void RWlock::lock_read()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        while (_writer > 0 || _pending > 0) {
            _cond.wait(lock);
        }
        ++_reader;
    }
    
    void RWlock::unlock_read()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        --_reader;
        if (_reader == 0) {
            _cond.notify_all();
        }
    }
    
    bool RWlock::try_lock_read()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        if (_writer > 0 || _pending > 0) {
            return false;
        }
        ++_reader;
        return true;
    }
    
    void RWlock::lock_write()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        ++_pending;
        while (_writer > 0 || _reader > 0) {
            _cond.wait(lock);
        }
        --_pending;
        ++_writer;
    }
    
    void RWlock::unlock_write()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        --_writer;
        _cond.notify_all();
    }
    
    bool RWlock::try_lock_write()
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        if (_writer > 0 || _reader > 0) {
            return false;
        }
        ++_writer;
        return true;
    }
    
    bool RWlock::is_writing() const
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        return _writer > 0;
    }
    
    bool RWlock::is_reading() const
    {
        std::unique_lock<decltype(_mutex)> lock(_mutex);
        return _reader > 0;
    }
    
}

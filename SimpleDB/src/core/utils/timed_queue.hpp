//
//  timed_queue.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef timed_queue_hpp
#define timed_queue_hpp

#include <chrono>
#include <condition_variable>
#include <list>
#include <mutex>
#include <stdio.h>
#include <string>
#include <thread>
#include <unordered_map>

namespace SDB {
    
    template <typename Key>
    class TimedQueue {
    public:
        TimedQueue(int delay)
        : _delay(std::chrono::seconds(delay))
        {};
        
        typedef std::function<void(const Key &)> OnExpired;
        
        void requeue(const Key &key)
        {
            std::lock_guard<std::mutex> lock_guard(_mutex);
            bool signal = _list.empty();
            
            auto iter = _map.find(key);
            if (iter != _map.end()) {
                _list.erase(iter->second);
                _map.erase(iter);
            }
            
            //delay
            _list.push_front({key, std::chrono::steady_clock::now() + _delay});
            auto last = _list.begin();
            _map.insert({key, last});
            if (signal) {
                _cond.notify_one();
            }
        }
        
        void wait_until_expired(const OnExpired &on_expired, bool forever = true)
        {
            {
                std::unique_lock<std::mutex> lock_guard(_mutex);
                while (_list.empty()) {
                    if (forever) {
                        _cond.wait(lock_guard);
                    } else {
                        return;
                    }
                }
            }
            bool got = false;
            while (!got) {
                Element element;
                Time now = std::chrono::steady_clock::now();
                {
                    std::unique_lock<std::mutex> lock_guard(_mutex);
                    element = _list.back();
                    if (now > element.second) {
                        _list.pop_back();
                        _map.erase(element.first);
                        got = true;
                    }
                }
                if (got) {
                    on_expired(element.first);
                } else {
                    std::this_thread::sleep_for(element.second - now);
                }
            }
        }
        
    protected:
        using Time = std::chrono::steady_clock::time_point;
        using Element = std::pair<Key, Time>;
        using List = std::list<Element>;
        using Map = std::unordered_map<Key, typename List::iterator>;
        Map _map;
        List _list;
        std::condition_variable _cond;
        std::mutex _mutex;
        std::chrono::seconds _delay;
    };
    
}

#endif /* timed_queue_hpp */

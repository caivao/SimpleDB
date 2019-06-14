//
//  trace.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#include "tracer.hpp"
#include "handle.hpp"
#include <sqlite3.h>

namespace SDB {
    
    Tracer::Tracer(void)
    : _time(0)
    , _in_transaction(false)
    , _performance_tracer_handle(nullptr)
    , _sql_tracer_handle(nullptr)
    {}
    
    void Tracer::set(const PerformanceTraceHandle &handle, void *context)
    {
        _performance_tracer_handle = handle;
        setup(context);
    }
    
    void Tracer::trace_performance(const std::string &sql, const int64_t &time)
    {
        auto iter = _performance_caches.find(sql);
        if (iter == _performance_caches.end()) {
            _performance_caches.insert({sql, 1});
        } else {
            ++iter->second;
        }
        _time += time;
    }
    
    void Tracer::report_performance(void)
    {
        if (!_performance_caches.empty() && _performance_tracer_handle) {
            _performance_tracer_handle(_performance_caches, _time);
            _performance_caches.clear();
            _time = 0;
        }
    }
    
    void Tracer::set(const SQLTraceHandle &handle, void *context)
    {
        _sql_tracer_handle = handle;
        setup(context);
    }
    
    void Tracer::report_sql(const std::string &sql)
    {
        if (_sql_tracer_handle) {
            _sql_tracer_handle(sql);
        }
    }
    
    void Tracer::setup(void *context)
    {
        unsigned int flag = 0;
        if (_sql_tracer_handle) {
            flag |= SQLITE_TRACE_STMT;
        }
        if (_performance_tracer_handle) {
            flag |= SQLITE_TRACE_PROFILE;
        }
        if (flag > 0) {
            auto callback = [](unsigned int flag, void *M, void *P, void *X) -> int {
                Tracer *tracer = (Tracer *)M;
                sqlite3_stmt *stmt = (sqlite3_stmt *) P;
                switch (flag) {
                    case SQLITE_TRACE_STMT: {
                        const char *sql = sqlite3_sql(stmt);
                        if (sql) {
                            tracer->report_sql(sql);
                        }
                    } break;
                    case SQLITE_TRACE_PROFILE: {
                        
                        sqlite3_int64 *time = (sqlite3_int64 *) X;
                        const char *sql = sqlite3_sql(stmt);
                        if (sql) {
                            tracer->trace_performance(sql, *time);
                        }
                        
                        if (!tracer->_in_transaction) {
                            tracer->report_performance();
                        }
                    } break;
                    default: break;
                }
                return SQLITE_OK;
            };
            sqlite3_trace_v2((sqlite3 *)context, flag, callback, this);
        } else {
            sqlite3_trace_v2((sqlite3 *)context, 0, nullptr, nullptr);
        }
    }
    
    void Tracer::enter_transaction(void)
    {
        _in_transaction = true;
    }
    
    void Tracer::exit_transaction(void)
    {
        _in_transaction = false;
    }
}

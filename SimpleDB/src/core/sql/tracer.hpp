//
//  trace.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/13.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef tracer_hpp
#define tracer_hpp

#include "declare.hpp"
#include <map>
#include <string>

namespace SDB {
    
    typedef std::function<void(const std::map<const std::string, unsigned int> &, const int64_t &)> PerformanceTraceHandle;
    typedef std::function<void(const std::string &)> SQLTraceHandle;
//    typedef std::function<void(Handle *, int, void *)> CommittedHookHandle;
    
    class Tracer {
    public:
        Tracer();
        
        void set(const PerformanceTraceHandle &handle, void *context);
        void trace_performance(const std::string &sql, const int64_t &time);
        void report_performance(void);
        
        void set(const SQLTraceHandle &handle, void *context);
        void report_sql(const std::string &sql);
        
        void setup(void *context);
        
        void enter_transaction(void);
        void exit_transaction(void);
    protected:
        PerformanceTraceHandle _performance_trace_handle;
        int64_t _time;
        bool _in_transaction;
        std::map<const std::string, unsigned int> _footprint;
        
        SQLTraceHandle _sql_trace_handle;
    };
}

#endif /* tracer_hpp */

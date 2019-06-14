//
//  handle.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef handle_hpp
#define handle_hpp

#include "declare.hpp"
#include "error.hpp"
#include "tracer.hpp"

#include <sqlite3.h>

namespace SDB {
    class Handle {
    public:
        Handle(const std::string &path);
        ~Handle(void);
        const std::string path;
        
        bool open(void);
        void close(void);
        
        std::shared_ptr<ValueBinder> prepare(const STMT::Statement &statement);
        bool exec(const STMT::Statement &statement);
        
        const Error &error(void) const;
        int changes(void);
        
        void set_tracer_handle(const PerformanceTraceHandle &handle);
        void set_tracer_handle(const SQLTraceHandle &handle);
        
    protected:
        Handle(const Handle &) = delete;
        Handle &operator=(const Handle &) = delete;
        void *_context;
        Error _error;
        Tracer _tracer;
    };
}

#endif /* handle_hpp */

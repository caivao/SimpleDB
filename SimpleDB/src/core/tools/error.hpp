//
//  error.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef error_hpp
#define error_hpp

#include <string>
#include "thread_share.hpp"

namespace SDB {
    class Error {
    public:
        
        Error(void);
        Error(const std::string &msg, int code);
        
        void reset(void);
        bool had_error(void) const;
        
        static void report(const std::string &msg, int code, Error *error);
        
    protected:
        std::string _msg;
        int _code;
        static ThreadShare<bool> _slient;
    };
}

#endif /* error_hpp */

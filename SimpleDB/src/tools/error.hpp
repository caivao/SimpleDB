//
//  error.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef error_hpp
#define error_hpp

#include <string>

namespace SDB {
    class Error {
    public:
        
        Error(void);
        Error(const std::string &msg, int code);
        
        void reset(void);
        bool had_error(void);
        
        static void report(const std::string &msg, int code, Error *error);
        
    protected:
        std::string _msg;
        int _code;
    };
}

#endif /* error_hpp */

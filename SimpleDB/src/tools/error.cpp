//
//  error.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "error.hpp"

namespace SDB {
    Error::Error(void)
    : _msg(""), _code(0)
    {}
    
    Error::Error(const std::string &msg, int code)
    : _msg(msg), _code(code)
    {}
    
    void Error::reset(void)
    {
        _code = 0;
        _msg = "";
    }
    
    bool Error::had_error(void)
    {
        return _code != 0 && _code != 200;
    }
    
    void Error::report(const std::string &msg, int code, Error *error)
    {
        Error innererror(msg, code);
//        innererror.report();
        
        if (error) {
            *error = innererror;
        }
    }
}

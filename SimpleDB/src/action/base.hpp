//
//  base.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include "declare.hpp"

namespace SDB {
    class Base {
    public:
//        const std::string get_path() const;
        virtual bool exec(const STMT::Statement &stmt, Error &error) = 0;
        
    };
}

#endif /* base_hpp */

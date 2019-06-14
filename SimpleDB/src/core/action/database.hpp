//
//  database.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include "declare.hpp"
#include "base.hpp"

namespace SDB {
    class Database : public Base {
    public:
        Database(const std::string &path);
        
        bool can_open(void);
        bool opened(void) const;
        void close(std::function<void(void)> on_closed);
        
        void blockade(void);
        void unblockade(void);
        bool blockaded(void);
        
        
    };
}

#endif /* database_hpp */

//
//  conflict.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef conflict_hpp
#define conflict_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    
    class Conflict : private Describable {
    public:
        static const Conflict &none;
        static const Conflict &rollback;
        static const Conflict &abort;
        static const Conflict &fail;
        static const Conflict &ignore;
        static const Conflict &replace;
        
        const std::string & get_conflict(void) const;
        
        bool operator !=(const Conflict & operand) const;
        bool operator ==(const Conflict & operand) const;
        
    private:
        
        enum class Type : int {
            none,
            rollback,
            abort,
            fail,
            ignore,
            replace,
        };
        
        Conflict(const Type type);
        Type type;
    };
    
}

#endif /* conflict_hpp */

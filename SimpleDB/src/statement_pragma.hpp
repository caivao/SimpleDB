//
//  statement_pragma.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_pragma_hpp
#define statement_pragma_hpp

#include "declare.hpp"
#include "statement.hpp"
#include "value_wrapper.hpp"
#include "pragma.hpp"

namespace SDB {
    
    namespace STMT {
        class Pragma : public Statement {
        public:
            
            Pragma &pragma(const SDB::Pragma &pragma);
            
            template <typename T>
            typename std::enable_if<std::is_arithmetic<T>::value
            || std::is_enum<T>::value
            || std::is_base_of<std::string, T>::value,
            Pragma &>::type
            operator =(const T &value) {
                _description.append(" = " + ValueWrapper(value).get_description());
                return *this;
            }
            
            Pragma &operator =(const char *value);
        };
    }
    
}

#endif /* statement_pragma_hpp */

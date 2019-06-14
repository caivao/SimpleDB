//
//  nested_query.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef nested_query_hpp
#define nested_query_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    class NestedQuery : public Describable {
    public:
        NestedQuery(const char *table);
        NestedQuery(const std::string &table);
        NestedQuery(const Join &join);
        NestedQuery(const STMT::Select &select);
        
        NestedQuery &as(const std::string &alias);
        operator NestedQueryList(void) const;
    };
}

#endif /* nested_query_hpp */

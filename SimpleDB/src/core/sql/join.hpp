//
//  join.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/11.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef join_hpp
#define join_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    class Join : public Describable {
    public:
        enum class Type : int {
            none,
            left,
            left_outer,
            inner,
            cross,
        };
        Join(void);
        Join(const std::string &table);
        
        Join &join(const NestedQuery &query, Type type = Type::none, bool is_natural = false);
        Join &on(const Expr &expr);
        
        template <typename T = Column>
        typename std::enable_if<std::is_base_of<Column, T>::value,
        Join &>::type
        usingg(const std::list<const T> &column_list)
        {
            _description.append(" USING ");
            component_join(column_list);
            return *this;
        }
    };
}

#endif /* join_hpp */

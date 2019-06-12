//
//  order.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/6.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef order_hpp
#define order_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    class Order : public Describable {
    public:
        class Term : private Describable {
        public:
            static const Term &none;
            static const Term &asc;
            static const Term &desc;
            
            const std::string &get_term(void) const;
            
            bool operator !=(const Term & operand) const;
            bool operator ==(const Term & operand) const;
            
        private:
            enum class Type : int {
                none,
                asc,
                desc,
            };
            Term(const Type type);
            Type type;
        };
        
        Order(const Expr &expr, const std::string &collation, Term term = Term::none);
        Order(const Expr &expr, Term term = Term::none);
        
        operator OrderList() const;
    };
}

#endif /* order_hpp */

//
//  statement.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef statement_hpp
#define statement_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    namespace STMT {
        class Statement : public Describable {
        public:
            Statement();
            const std::string &sql(void) const;
//            virtual ~Statement();
        };
    }
}

#endif /* statement_hpp */

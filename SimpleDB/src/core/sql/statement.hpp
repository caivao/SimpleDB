//
//  statement.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
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
            Statement(void);
            const std::string &sql(void) const;
            virtual std::shared_ptr<ValueBinder> prepare(const void *context, Tracer &tracer, Error &error) const;
            virtual bool exec(const void *context, Tracer &tracer, Error &error) const;
            virtual ~Statement(void);
        };
    }
}

#endif /* statement_hpp */

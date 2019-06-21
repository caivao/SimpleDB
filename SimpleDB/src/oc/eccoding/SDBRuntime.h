//
//  SDBProperty.h
//  SimpleDB
//
//  Created by OYOL on 2019/6/20.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef SDBProperty_h
#define SDBProperty_h

#import <Foundation/Foundation.h>
#include <string>

namespace SDB {
    namespace OC {
        namespace Runtime {
            using InstanceType = id;
            using OCType = id;
            using Setter = void (^)(InstanceType, OCType);
            using Getter = OCType (^)(InstanceType);
            
            SEL getter_sel(Class cls, const std::string &property_name);
            SEL setter_sel(Class cls, const std::string &property_name);
            IMP class_method_imp(Class cls, SEL sel);
            IMP instance_method_imp(Class, SEL sel);
            Class property_class(Class owner, const std::string &property_name);
            
            template <typename PropertyType>
            class Accessor {
            public:
                using Setter = void (^)(InstanceType, PropertyType);
                using Getter = PropertyType (^)(InstanceType);
            };
        }
    }
}

#endif /* SDBProperty_h */

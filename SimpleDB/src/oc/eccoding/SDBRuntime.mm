//
//  SDBProperty.m
//  SimpleDB
//
//  Created by OYOL on 2019/6/20.
//  Copyright © 2019 feng. All rights reserved.
//

#import "SDBRuntime.h"
#include "error.hpp"
#include <objc/runtime.h>
#include <objc/message.h>

namespace SDB {
    namespace OC {
        namespace Runtime {
            
            SEL getter_sel(Class cls, const std::string &property_name)
            {
                objc_property_t property = class_getProperty(cls, property_name.c_str());
                const char *getter = property_copyAttributeValue(property, "G");
                if (!getter) {
                    getter = property_name.c_str();
                }
                return sel_registerName(getter);
            }
            
            SEL setter_sel(Class cls, const std::string &property_name)
            {
                objc_property_t property = class_getProperty(cls, property_name.c_str());
                const char *setter = property_copyAttributeValue(property, "S");
                if (setter) {
                    return sel_registerName(setter);
                }
                std::string defaultSetter = "set" + property_name + ":";
                defaultSetter[3] = std::toupper(property_name[0]);
                return sel_registerName(defaultSetter.c_str());
            }
            
            IMP class_method_imp(Class cls, SEL sel)
            {
                return [cls methodForSelector:sel];
            }
            
            IMP instance_method_imp(Class cls, SEL sel)
            {
                return [cls instanceMethodForSelector:sel];
            }
            
            Class property_class(Class owner, const std::string &property_name)
            {
                objc_property_t property = class_getProperty(owner, property_name.c_str());
                NSString *attributes = [NSString stringWithUTF8String:property_getAttributes(property)];
                NSArray *splitAttributes = [attributes componentsSeparatedByString:@","];
                if (splitAttributes.count > 0) {
                    NSString *encode_type = splitAttributes[0];
                    NSArray *split_encode_types = [encode_type componentsSeparatedByString:@"\""];
                    if (split_encode_types.count <= 1) {
//                        SDB::Error::Abort(("Failed to parse the type of [" + propertyName + "]").c_str());
                        return nil;
                    }
                    NSString *class_str = split_encode_types[1];
                    return NSClassFromString(class_str);
                }
                return nil;
            }
        }
    }
}

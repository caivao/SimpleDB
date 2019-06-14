//
//  describable.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef describable_hpp
#define describable_hpp

#include <string>
#include <list>
#include <iostream>

namespace SDB {
    class Describable {
    public:
        template <typename T>
        static std::string get_component_join(const std::list<const T> &list)
        {
            std::string description;
            component_join(list, description);
            return description;
        }
        
        template <typename T>
        void component_join(const std::list<const T> &list,
                            const std::string &separator = ", ")
        {
            component_join(list, _description, separator);
        }
        
        const std::string &description(void) const;
        explicit operator const std::string &(void) const;
        
        bool empty(void) const;
        
        friend std::ostream & operator <<(std::ostream &out, const Describable & expr);
        
        void print(void) const;
        
    protected:
        template <typename T>
        static void component_join(const std::list<const T> &list,
                                   std::string &output,
                                   const std::string &separator = ", ")
        {
            bool flag = false;
            for (const auto & component : list) {
                if(flag) {
                    output.append(separator);
                } else {
                    flag = true;
                }
                output.append(std::string(component));
            }
        }
        
        Describable(const std::string &description);
        Describable(const char *description);
        
        ~Describable(void);
        
        std::string _description;
    };
}

#endif /* describable_hpp */

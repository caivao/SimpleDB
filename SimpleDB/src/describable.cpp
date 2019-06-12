//
//  describable.cpp
//  SimpleDB
//
//  Created by OYO on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "describable.hpp"

namespace SDB {
    
    Describable::Describable(const std::string &description)
    : _description(description)
    {}
    
    Describable::Describable(const char *description)
    : _description(std::string(description))
    {}
    
    Describable::~Describable()
    {
//        std::cout << _description << std::endl;
    }
    
    const std::string &Describable::get_description() const
    {
        return _description;
    }
    
    Describable::operator const std::string &() const
    {
        return _description;
    }
    
    bool Describable::empty() const {
        return _description.empty();
    }
    
    std::ostream & operator <<(std::ostream &out, const Describable & expr)
    {
        out << expr.get_description();
        return out;
    }
    
    void Describable::print(void) const
    {
        std::cout << _description << std::endl;
    }
}

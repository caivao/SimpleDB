//
//  path.hpp
//  SimpleDB
//
//  Created by OYO on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef path_hpp
#define path_hpp

#include <string>

namespace SDB {
    namespace Path {
        std::string add_extention(const std::string &base, const std::string &extention);
        std::string add_component(const std::string &base, const std::string &component);
        std::string file_name(const std::string &path);
        std::string file_base_name(const std::string &path);
        std::string file_extension(const std::string &path);
    }
}

#endif /* path_hpp */

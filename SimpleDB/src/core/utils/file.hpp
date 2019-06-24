//
//  file.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <string>
#include <list>
#include "error.hpp"

namespace SDB {
    namespace File {
        bool file_exists(const std::string &path, bool *is_directory, Error &error);
        size_t file_size(const std::string &path);
        size_t file_size(const std::list<std::string> &path_set, Error &error);
        
        bool create_directory(const std::string &path, Error &error);
        bool create_directory_recursive(const std::string &path, Error &error);
        
        bool remove_file(const std::string &path, Error &error);
        bool remove_file(const std::list<std::string> &path_set, Error &error);
        bool move_file(const std::list<std::string> &path_set, const std::string &destination, Error &error);
    }
}

#endif /* file_hpp */

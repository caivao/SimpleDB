//
//  file.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "file.hpp"
#include "path.hpp"
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

namespace SDB {
    namespace File {
        bool file_exists(const std::string &path, bool *is_directory, Error &error)
        {
            if (access(path.c_str(), F_OK) == 0) {
                error.reset();
                return true;
            } else if (errno == ENOENT) {
                error.reset();
                return false;
            }
            Error::report(strerror(errno), errno, &error);
            
            if(is_directory) {
                struct stat temp;
                if(lstat(path.c_str(), &temp) != 0) {
                    *is_directory = S_ISDIR(temp.st_mode);
                }
            }
            
            return false;
        }
        
        size_t file_size(const std::string &path, Error &error)
        {
            struct stat temp;
            if (lstat(path.c_str(), &temp) == 0) {
                error.reset();
                return (size_t) temp.st_size;
            } else if (errno == ENOENT) {
                error.reset();
                return 0;
            }
            Error::report(strerror(errno), errno, &error);
            return 0;
        }
        
        size_t file_size(const std::list<std::string> &path_set, Error &error)
        {
            size_t size = 0;
            for (const auto &path : path_set) {
                size += file_size(path, error);
                if (error.had_error()) {
                    return 0;
                }
            }
            return size;
        }
        
        bool create_directory(const std::string &path, Error &error)
        {
            if (mkdir(path.c_str(), 0755) == 0) {
                return true;
            }
            Error::report(strerror(errno), errno, &error);
            return false;
        }
        
        bool create_directory_recursive(const std::string &path, Error &error)
        {
            bool is_directory = true;
            if (!file_exists(path, &is_directory, error)
                && (error.had_error()
                || !is_directory
                || !create_directory_recursive(Path::file_base_name(path), error)
                || !create_directory(path, error))) {
                return false;
            }
            return true;
        }
        
        bool remove_file(const std::string &path, Error &error)
        {
            if (remove(path.c_str()) == 0 || errno == ENOENT) {
                return true;
            }
            Error::report(strerror(errno), errno, &error);
            return false;
        }
        
        bool remove_file(const std::list<std::string> &path_set, Error &error)
        {
            for (const auto &path : path_set) {
                if (!remove_file(path, error)) {
                    return false;
                }
            }
            return true;
        }
        
        bool move_file(const std::list<std::string> &path_set, const std::string &destination, Error &error)
        {
            return true;
        }
    }
}

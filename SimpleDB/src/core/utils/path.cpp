//
//  path.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/12.
//  Copyright © 2019 feng. All rights reserved.
//

#include "path.hpp"
#include <libgen.h>

namespace SDB {
    namespace Path {
        std::string add_extention(const std::string &base, const std::string &extention)
        {
            if(extention.empty()) {
                return base;
            }
            if(extention[0] == '.') {
                return base + extention;
            }
            return base + "." + extention;
        }
        
        std::string add_component(const std::string &base, const std::string &component)
        {
            std::string path = base;
            if (path[path.size() - 1] != '/') {
                path.append("/");
            }
            path.append(component);
            return path;
        }
        
        std::string file_name(const std::string &path)
        {
            size_t size = path.size();
            bool find_last = true;
            const char *cstr = path.c_str();
            size_t begin = 0, end = 0, length = 0;
            for (size_t i = 0; i < size; ++i) {
                size_t pos = size - i - 1;
                if (find_last) {
                    if (cstr[pos] != '/') {
                        end = pos;
                        find_last = false;
                    }
                } else {
                    if (cstr[pos] == '/') {
                        length = end - pos;
                        begin = pos + 1;
                        break;
                    }
                }
            }
            return length != 0 && size > 0 ? std::string(cstr, begin, length) : "/";
        }
        
        std::string file_base_name(const std::string &path)
        {
            std::string dir = path;
            dir = dirname(&(*dir.begin()));
            return dir;
        }
        
        std::string file_extension(const std::string &path)
        {
            size_t size = path.size();
            bool find_last = true;
            const char *cstr = path.c_str();
            size_t begin = 0, end = 0, length = 0;
            for (size_t i = 0; i < size; ++i) {
                size_t pos = size - i - 1;
                if (find_last) {
                    if (cstr[pos] != '.') {
                        end = pos;
                        find_last = false;
                    }
                } else {
                    if (cstr[pos] == '.') {
                        length = end - pos;
                        begin = pos + 1;
                        break;
                    }
                }
            }
            return length != 0 && size > 0 ? std::string(cstr, begin, length) : "";
        }
    }
}

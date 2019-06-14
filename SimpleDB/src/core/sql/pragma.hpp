//
//  pragma.hpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#ifndef pragma_hpp
#define pragma_hpp

#include "declare.hpp"
#include "describable.hpp"

namespace SDB {
    
    class Pragma : public Describable {
    public:
        static const Pragma application_id;
        static const Pragma auto_vacuum;
        static const Pragma automatic_index;
        static const Pragma busy_timeout;
        static const Pragma cache_size;
        static const Pragma cache_spill;
        static const Pragma case_sensitive_like;
        static const Pragma cell_size_check;
        static const Pragma checkpoint_fullfsync;
        static const Pragma cipher;
        static const Pragma cipher_add_random;
        static const Pragma cipher_default_kdf_iter;
        static const Pragma cipher_default_page_size;
        static const Pragma cipher_page_size;
        static const Pragma cipher_default_use_hmac;
        static const Pragma cipher_migrate;
        static const Pragma cipher_profile;
        static const Pragma cipher_provider;
        static const Pragma cipher_provider_version;
        static const Pragma cipher_use_hmac;
        static const Pragma cipher_version;
        static const Pragma collation_list;
        static const Pragma compile_options;
        static const Pragma count_changes;
        static const Pragma data_store_directory;
        static const Pragma data_version;
        static const Pragma database_list;
        static const Pragma default_cache_size;
        static const Pragma defer_foreign_keys;
        static const Pragma empty_result_callbacks;
        static const Pragma encoding;
        static const Pragma foreign_key_check;
        static const Pragma foreign_key_list;
        static const Pragma foreign_keys;
        static const Pragma freelist_count;
        static const Pragma full_column_names;
        static const Pragma fullfsync;
        static const Pragma ignore_check_constraints;
        static const Pragma incremental_vacuum;
        static const Pragma index_info;
        static const Pragma index_list;
        static const Pragma index_xinfo;
        static const Pragma integrity_check;
        static const Pragma journal_mode;
        static const Pragma journal_size_limit;
        static const Pragma key;
        static const Pragma kdf_iter;
        static const Pragma legacy_file_format;
        static const Pragma locking_mode;
        static const Pragma max_page_count;
        static const Pragma mmap_size;
        static const Pragma page_count;
        static const Pragma page_size;
        static const Pragma parser_trace;
        static const Pragma query_only;
        static const Pragma quick_check;
        static const Pragma read_uncommitted;
        static const Pragma recursive_triggers;
        static const Pragma rekey;
        static const Pragma reverse_unordered_selects;
        static const Pragma schema_version;
        static const Pragma secure_delete;
        static const Pragma short_column_names;
        static const Pragma shrink_memory;
        static const Pragma soft_heap_limit;
        static const Pragma stats;
        static const Pragma synchronous;
        static const Pragma table_info;
        static const Pragma temp_store;
        static const Pragma temp_store_directory;
        static const Pragma threads;
        static const Pragma user_version;
        static const Pragma vdbe_addoptrace;
        static const Pragma vdbe_debug;
        static const Pragma vdbe_listing;
        static const Pragma vdbe_trace;
        static const Pragma wal_autocheckpoint;
        static const Pragma wal_checkpoint;
        static const Pragma writable_schema;
        
        const std::string &get_name(void) const;
        
    protected:
        Pragma(const char *name);
    };
    
}

#endif /* pragma_hpp */

//
//  pragma.cpp
//  SimpleDB
//
//  Created by lifeng on 2019/6/5.
//  Copyright © 2019 feng. All rights reserved.
//

#include "pragma.hpp"

namespace SDB {
    
    const Pragma Pragma::application_id("application_id");
    const Pragma Pragma::auto_vacuum("auto_vacuum");
    const Pragma Pragma::automatic_index("automatic_index");
    const Pragma Pragma::busy_timeout("busy_timeout");
    const Pragma Pragma::cache_size("cache_size");
    const Pragma Pragma::cache_spill("cache_spill");
    const Pragma Pragma::case_sensitive_like("case_sensitive_like");
    const Pragma Pragma::cell_size_check("cell_size_check");
    const Pragma Pragma::checkpoint_fullfsync("checkpoint_fullfsync");
    const Pragma Pragma::cipher("cipher");
    const Pragma Pragma::cipher_add_random("cipher_add_random");
    const Pragma Pragma::cipher_default_kdf_iter("cipher_default_kdf_iter");
    const Pragma Pragma::cipher_default_page_size("cipher_default_page_size");
    const Pragma Pragma::cipher_page_size("cipher_page_size");
    const Pragma Pragma::cipher_default_use_hmac("cipher_default_use_hmac");
    const Pragma Pragma::cipher_migrate("cipher_migrate");
    const Pragma Pragma::cipher_profile("cipher_profile");
    const Pragma Pragma::cipher_provider("cipher_provider");
    const Pragma Pragma::cipher_provider_version("cipher_provider_version");
    const Pragma Pragma::cipher_use_hmac("cipher_use_hmac");
    const Pragma Pragma::cipher_version("cipher_version");
    const Pragma Pragma::collation_list("collation_list");
    const Pragma Pragma::compile_options("compile_options");
    const Pragma Pragma::count_changes("count_changes");
    const Pragma Pragma::data_store_directory("data_store_directory");
    const Pragma Pragma::data_version("data_version");
    const Pragma Pragma::database_list("database_list");
    const Pragma Pragma::default_cache_size("default_cache_size");
    const Pragma Pragma::defer_foreign_keys("defer_foreign_keys");
    const Pragma Pragma::empty_result_callbacks("empty_result_callbacks");
    const Pragma Pragma::encoding("encoding");
    const Pragma Pragma::foreign_key_check("foreign_key_check");
    const Pragma Pragma::foreign_key_list("foreign_key_list");
    const Pragma Pragma::foreign_keys("foreign_keys");
    const Pragma Pragma::freelist_count("freelist_count");
    const Pragma Pragma::full_column_names("full_column_names");
    const Pragma Pragma::fullfsync("fullfsync");
    const Pragma Pragma::ignore_check_constraints("ignore_check_constraints");
    const Pragma Pragma::incremental_vacuum("incremental_vacuum");
    const Pragma Pragma::index_info("index_info");
    const Pragma Pragma::index_list("index_list");
    const Pragma Pragma::index_xinfo("index_xinfo");
    const Pragma Pragma::integrity_check("integrity_check");
    const Pragma Pragma::journal_mode("journal_mode");
    const Pragma Pragma::journal_size_limit("journal_size_limit");
    const Pragma Pragma::key("key");
    const Pragma Pragma::kdf_iter("kdf_iter");
    const Pragma Pragma::legacy_file_format("legacy_file_format");
    const Pragma Pragma::locking_mode("locking_mode");
    const Pragma Pragma::max_page_count("max_page_count");
    const Pragma Pragma::mmap_size("mmap_size");
    const Pragma Pragma::page_count("page_count");
    const Pragma Pragma::page_size("page_size");
    const Pragma Pragma::parser_trace("parser_trace");
    const Pragma Pragma::query_only("query_only");
    const Pragma Pragma::quick_check("quick_check");
    const Pragma Pragma::read_uncommitted("read_uncommitted");
    const Pragma Pragma::recursive_triggers("recursive_triggers");
    const Pragma Pragma::rekey("rekey");
    const Pragma Pragma::reverse_unordered_selects("reverse_unordered_selects");
    const Pragma Pragma::schema_version("schema_version");
    const Pragma Pragma::secure_delete("secure_delete");
    const Pragma Pragma::short_column_names("short_column_names");
    const Pragma Pragma::shrink_memory("shrink_memory");
    const Pragma Pragma::soft_heap_limit("soft_heap_limit");
    const Pragma Pragma::stats("stats");
    const Pragma Pragma::synchronous("synchronous");
    const Pragma Pragma::table_info("table_info");
    const Pragma Pragma::temp_store("temp_store");
    const Pragma Pragma::temp_store_directory("temp_store_directory");
    const Pragma Pragma::threads("threads");
    const Pragma Pragma::user_version("user_version");
    const Pragma Pragma::vdbe_addoptrace("vdbe_addoptrace");
    const Pragma Pragma::vdbe_debug("vdbe_debug");
    const Pragma Pragma::vdbe_listing("vdbe_listing");
    const Pragma Pragma::vdbe_trace("vdbe_trace");
    const Pragma Pragma::wal_autocheckpoint("wal_autocheckpoint");
    const Pragma Pragma::wal_checkpoint("wal_checkpoint");
    const Pragma Pragma::writable_schema("writable_schema");
    
    const std::string &Pragma::get_name() const
    {
        return _description;
    }
    
    Pragma::Pragma(const char *name)
    : Describable(name)
    {}
    
}

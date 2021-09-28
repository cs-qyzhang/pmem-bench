#pragma once

#include <stddef.h>

struct pmem_ctx {
    char*   file_path;
    size_t  file_size;
    size_t  align;
    size_t  mapped_len;
    int     is_pmem;
    void*   pmem_addr;

    char*   flush_method;
    char*   fence_method;
};

extern void pmem_init(struct pmem_ctx* pmem_ctx);
extern void pmem_fini(struct pmem_ctx* ctx);
#pragma once

#include <stddef.h>

enum MapType {
    MAP_TYPE_LIBPMEM,
    MAP_TYPE_MMAP,
};

struct MapInfo {
    enum MapType map_type;

    char *       file_path;
    size_t       file_size;
    size_t       align;
    size_t       blk_size;
    size_t       mapped_len;
    int          is_pmem;
    void *       map_addr;

    char *       flush_method;
    char *       fence_method;
};

extern void map_init();
extern void map_fini();
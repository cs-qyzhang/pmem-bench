#include <stdio.h>
#include "util/mapping.h"
#include "config.h"

int main(void) {
    struct MapInfo map = {
        .map_type = MAP_TYPE_LIBPMEM,
        .align = 4096,
        .blk_size = 4096,
        .file_size = (1024UL * 1024UL * 8UL),
        .file_path = "/mnt/pmem0/pmem_test",
    };
    map_init(&map);
    printf("map addr: %p, mapped size: %lu, is pmem: %s\n",
           map.map_addr, map.mapped_len, map.is_pmem ? "true" : "false");
    printf("flush method: %s, fence method: %s\n",
           map.flush_method, map.fence_method);
    map_init(&map);
    return 0;
}
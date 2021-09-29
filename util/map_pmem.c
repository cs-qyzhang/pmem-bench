#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <libpmem.h>
#include "util/mapping.h"
#include "config.h"

void libpmem_init(struct MapInfo* map) {
    assert(map->map_type == MAP_TYPE_LIBPMEM);
    // remove pmem file
    char cmd_buf[1024];
    sprintf(cmd_buf, "rm -rf %s", map->file_path);
    system(cmd_buf);

    map->map_addr = pmem_map_file(map->file_path, map->file_size + map->align,
                                       PMEM_FILE_CREATE | PMEM_FILE_EXCL,
                                       0666, &map->mapped_len, &map->is_pmem);
    if (map->map_addr == NULL) {
        perror("pmem_map_file");
        exit(1);
    }
}

void libpmem_fini(struct MapInfo* map) {
    assert(map->map_type == MAP_TYPE_LIBPMEM);
    pmem_unmap(map->map_addr, map->mapped_len);
}
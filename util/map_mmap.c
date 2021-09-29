#include <assert.h>
#include <sys/mman.h>
#include "util/mapping.h"

void mmap_init(struct MapInfo* map) {
    assert(map->map_type == MAP_TYPE_MMAP);
}

void mmap_fini(struct MapInfo* map) {
    assert(map->map_type == MAP_TYPE_MMAP);
}
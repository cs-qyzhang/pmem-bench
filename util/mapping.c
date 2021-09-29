#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <x86intrin.h>
#include <libpmem.h>
#include "util/mapping.h"
#include "config.h"

extern void mmap_init(struct MapInfo* map);
extern void mmap_fini(struct MapInfo* map);
extern void libpmem_init(struct MapInfo* map);
extern void libpmem_fini(struct MapInfo* map);

#if defined(USE_CLWB)
    #define myflush(addr, len)      _mm_clwb((addr))
    #define myfence()               _mm_sfence()
    static const char* flush_method = "clwb";
    static const char* fence_method = "sfence";
#elif defined(USE_CLFLUSHOPT)
    #define myflush(addr, len)      _mm_clflushopt((addr))
    #define myfence()               _mm_sfence()
    static const char* flush_method = "clflushopt";
    static const char* fence_method = "sfence";
#elif defined(USE_CLFLUSH)
    #define myflush(addr, len)      _mm_clflush((addr))
    #define myfence()
    static const char* flush_method = "clflush";
    static const char* fence_method = "none";
#elif defined(USE_LIBPMEM)
    #define myflush(addr, len)      pmem_flush((addr), (len))
    #define myfence()               pmem_drain()
    static const char* flush_method = "pmem_flush()";
    static const char* fence_method = "pmem_drain()";
#elif defined(__CLWB__)             /* defined by -march compiler options */
    #define myflush(addr, len)      _mm_clwb((addr))
    #define myfence()               _mm_sfence()
    static const char* flush_method = "clwb";
    static const char* fence_method = "sfence";
#elif defined(__CLFLUSHOPT__)
    #define myflush(addr, len)      _mm_clflushopt((addr))
    #define myfence()               _mm_sfence()
    static const char* flush_method = "clflushopt";
    static const char* fence_method = "sfence";
#elif defined(__CLFLUSH__)
    #define myflush(addr, len)      _mm_clflush((addr))
    #define myfence()
    static const char* flush_method = "clflush";
    static const char* fence_method = "none";
#else
    static_assert(0, "cannot find CLWB/CLFLUSHOPT/CLFLUSH instruction!");
#endif

void map_init(struct MapInfo* map) {
    map->flush_method = (char*)malloc(strlen(flush_method) + 1);
    map->fence_method = (char*)malloc(strlen(fence_method) + 1);
    strcpy(map->flush_method, flush_method);
    strcpy(map->fence_method, flush_method);

    switch (map->map_type) {
    case MAP_TYPE_LIBPMEM:
        libpmem_init(map);
        break;
    case MAP_TYPE_MMAP:
        mmap_init(map);
        break;
    default:
        assert(0);
    }
}

void map_fini(struct MapInfo* map) {
    switch (map->map_type) {
    case MAP_TYPE_LIBPMEM:
        libpmem_fini(map);
        break;
    case MAP_TYPE_MMAP:
        mmap_fini(map);
        break;
    default:
        assert(0);
    }
}
#include <libpmem.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util/pmem.h"
#include "config.h"

#ifdef USE_CLWB
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

void pmem_init(struct pmem_ctx* ctx) {
    // remove pmem file
    char cmd_buf[1024];
    sprintf(cmd_buf, "rm -rf %s", ctx->file_path);
    system(cmd_buf);

    ctx->pmem_addr = pmem_map_file(ctx->file_path, ctx->file_size + ctx->align,
                                   PMEM_FILE_CREATE | PMEM_FILE_EXCL,
                                   0666, &ctx->mapped_len, &ctx->is_pmem);
    if (ctx->pmem_addr == NULL) {
        perror("pmem_map_file");
        exit(1);
    }

    ctx->flush_method = (char*)malloc(strlen(flush_method) + 1);
    ctx->fence_method = (char*)malloc(strlen(fence_method) + 1);
    strcpy(ctx->flush_method, flush_method);
    strcpy(ctx->fence_method, flush_method);
}

void pmem_fini(struct pmem_ctx* ctx) {
    pmem_unmap(ctx->pmem_addr, ctx->mapped_len);
}
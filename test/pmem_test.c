#include <stdio.h>
#include "util/pmem.h"
#include "config.h"

int main(void) {
    struct pmem_ctx ctx = {
        .align = 4096,
        .file_size = (1024UL * 1024UL * 8UL),
        .file_path = "/mnt/pmem0/pmem_test",
    };
    pmem_init(&ctx);
    printf("pmem addr: %p, mapped size: %lu, is pmem: %s\n",
           ctx.pmem_addr, ctx.mapped_len, ctx.is_pmem ? "true" : "false");
    printf("flush method: %s, fence method: %s\n",
           ctx.flush_method, ctx.fence_method);
    pmem_fini(&ctx);
    return 0;
}
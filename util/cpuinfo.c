#ifndef NDEBUG
#include <stdio.h>
#endif // NDEBUG

void get_cpuinfo(int *ncores, int *nthreads, int *ht) {
    unsigned int ncores_ = 0;
    unsigned int nthreads_ = 0;
    unsigned int ht_ = 0;

    __asm__ volatile("cpuid"
                    : "=a"(ncores_), "=b"(nthreads_)
                    : "a"(0xb), "c"(0x1)
                    :);

    if (ncores)
        *ncores = ncores_;
    if (nthreads)
        *nthreads = nthreads_;
    if (ht)
        *ht = (ncores_ != nthreads_) ? 1 : 0;

#ifndef NDEBUG
    printf("core: %d, threads: %d, hyper-threading: %s\n",
           ncores_, nthreads_, ht_ ? "enabled" : "disabled");
#endif // NDEBUG
}

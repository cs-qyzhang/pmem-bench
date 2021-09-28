#undef NDEBUG

#include <stdio.h>
#include "util/cpuinfo.h"

int main(void) {
    int ncores, nthreads, hyper_threading;
    get_cpuinfo(&ncores, &nthreads, &hyper_threading);

    return 0;
}
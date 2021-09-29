#undef NDEBUG

#include <stdio.h>
#include "util/uarch.h"

int main(void) {
    int ncores, nthreads, hyper_threading;
    get_cpuinfo(&ncores, &nthreads, &hyper_threading);

    return 0;
}
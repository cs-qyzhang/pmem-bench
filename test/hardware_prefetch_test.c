#include <stdio.h>
#include "util/uarch.h"

int main(void) {
    disable_prefetch_all();
    enable_prefetch_all();

    return 0;
}
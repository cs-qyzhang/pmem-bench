#include <stdio.h>
#include "util/hardware_prefetch.h"

int main(void) {
    disable_prefetch_all();
    enable_prefetch_all();

    return 0;
}
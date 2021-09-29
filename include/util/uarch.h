#pragma once

extern void get_cpuinfo(int* ncores, int* nthreads, int* ht);
extern void disable_prefetch_all();
extern void enable_prefetch_all();
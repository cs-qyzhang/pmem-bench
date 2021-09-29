project(bench)
cmake_minimum_required(VERSION 3.8)

option(USE_LIBPMEM      "" ON)
option(USE_CLWB         "" OFF)
option(USE_CLFLUSHOPT   "" OFF)
option(USE_CLFLUSH      "" OFF)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
               "${PROJECT_SOURCE_DIR}/include/config.h")

include_directories(include)

add_compile_options(-march=native -Wall)

## utility
add_library(uarch STATIC util/cpuinfo.c util/hardware_prefetch.c)

add_library(mapping STATIC util/mapping.c util/map_pmem.c util/map_mmap.c)
target_link_libraries(mapping pmem)

## test
add_executable(hw_prefetch_test test/hardware_prefetch_test.c)
target_link_libraries(hw_prefetch_test uarch)

add_executable(cpuinfo_test test/cpuinfo_test.c)
target_link_libraries(cpuinfo_test uarch)

add_executable(pmem_map_test test/pmem_map_test.c)
target_link_libraries(pmem_map_test mapping)
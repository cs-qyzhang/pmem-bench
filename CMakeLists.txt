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
add_library(cpuinfo STATIC util/cpuinfo.c)

add_library(hw_prefetch STATIC util/hardware_prefetch.c util/cpuinfo.c)
target_link_libraries(hw_prefetch cpuinfo)

add_library(mypmem STATIC util/pmem.c)

## test
add_executable(hw_prefetch_test test/hardware_prefetch_test.c)
target_link_libraries(hw_prefetch_test hw_prefetch)

add_executable(cpuinfo_test test/cpuinfo_test.c)
target_link_libraries(cpuinfo_test cpuinfo)

add_executable(pmem_test test/pmem_test.c)
target_link_libraries(pmem_test mypmem)
if(USE_LIBPMEM)
    target_link_libraries(pmem_test pmem)
endif()
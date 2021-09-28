# pmem-bench

Evaluation of persistent memory.

## Build

```bash
$ mkdir build && cd build
$ cmake ..
$ make
```

## File Description

### utility

* `cpuinfo`: Get number of cpu cores etc.
* `hardware_prefetch`: Enable/disable hardware prefetch to avoid impact on evaluation. Borrowed from [uarch-configure](https://github.com/deater/uarch-configure).
* `pmem`: Commonly used pmem operations such as initializing.

### script

* `init_pmem.sh`: Used to initialize pmem device which is simulated by using `memmap` kernel parameter.

#!/bin/bash
# This is used to init tweaked pmem after boot.
# pmem is tweaked by using "memmap" kernel parameter.

sudo mkfs.ext4 /dev/pmem0
sudo mount -o dax /dev/pmem0 /mnt/pmem0
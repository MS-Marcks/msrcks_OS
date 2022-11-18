file /mnt/c/msrcks_OS/build/bin/kernel.elf
target remote 192.168.1.7:1234
set disassembly-flavor intel
b _start
c

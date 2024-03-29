#include "print/printf/printf.h"
#include "bootloader/bootservices.h"
#include "util/string.h"
#include "memory/memory.h"
#include "io/interrupts.h"
#include "memory/paging.h"
/*#include "dev/acpi/acpi.h"*/
#include "dev/device.h"
#include <stdint.h>

void hlt()
{
    __asm__("hlt");
}

void _start()
{
    printf("Loading kernel, bootloader=%s, version=%s\n",
           get_bootloader_name(),
           get_bootloader_version());

    init_memory();
    init_interrupts();
    init_paging();
    init_devices();
    device_list();

    printf("Kernel looping\n");
    hlt();
}

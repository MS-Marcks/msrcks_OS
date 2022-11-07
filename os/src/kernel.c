#include "print/printf/printf.h"
#include "bootloader/bootservices.h"
#include "util/string.h"
#include "memory/memory.h"
#include <stdint.h>
#include "io/interrupts.h"
#include "memory/paging.h"

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

    void *ptr = request_page();
    memset((void *)ptr, 0x5, 0x1000);

    map_memory((void *)0xffffffffdeadb000, ptr);
    map_memory((void *)0xffffffffcafeb000, ptr);

    uint64_t *ptr1 = (uint64_t *)0xffffffffdeadb000;
    uint64_t *ptr2 = (uint64_t *)0xffffffffcafeb000;

    mprotect((void *)ptr2, 0x1000, 0x0);

    printf("%llx\n", *ptr1);
    memset((void *)ptr2, 0x6, 0x1000);
    printf("%llx\n", *ptr1);

    // uint64_t *badptr = (uint64_t *)0xffffffffdeadb000;
    //*badptr = 0xdeadbeef;

    /*void *page1 = request_page();
    printf("Page 1: %p\n", page1);
    void *page2 = request_page();
    printf("Page 2: %p\n", page2);
    free_page(page2);
    void *page3 = request_page();
    printf("Page 3: %p\n", page3);*/

    printf("Kernel looping\n");
    hlt();
}
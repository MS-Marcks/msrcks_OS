#include "idt.h"

void set_offset(struct idtdescentry *entry, uint64_t address)
{
    entry->offset_1 = (uint16_t)(address & 0x000000000000ffff);
    entry->offset_2 = (uint16_t)((address & 0x00000000ffff0000) >> 16);
    entry->offset_3 = (uint32_t)((address & 0xffffffff00000000) >> 32);
}
uint64_t get_offest(struct idtdescentry *entry)
{
    uint64_t offest = 0;
    offest |= (uint64_t)entry->offset_1;
    offest |= (uint64_t)entry->offset_2 << 16;
    offest |= (uint64_t)entry->offset_3 << 32;

    return offest;
}
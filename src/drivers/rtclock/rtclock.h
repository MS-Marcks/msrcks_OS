#ifndef _RTCLOCK_H
#define _RTCLOCK_H


#define BCD_TO_BIN(bcd) ((bcd / 16) * 10) + (bcd & 0xf) 

#include <stdint.h>

#define BIT_SECOND 0x00
#define BIT_MINUTE 0x02
#define BIT_HOUR 0x04
#define BIT_DAY 0x07
#define BIT_MONTH 0x08
#define BIT_YEAR 0x09
#define BIT_CENTURY 0x32
#define BIT_REGA 0x0A
#define BIT_REGB 0x0B   

struct rtclock
{
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned short year;
    unsigned char is_24;
    unsigned char is_binary;
};


unsigned char read_CMOS(unsigned int reg);
void init_rtclock();

#endif
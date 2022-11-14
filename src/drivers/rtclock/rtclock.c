#include "rtclock.h"
#include "../../print/printf/printf.h"
#include <sys/io.h>

struct rtclock clock;
struct rtclock clock_local;

unsigned char read_CMOS(unsigned int reg)
{
    unsigned char value;
    __asm__("cli");
    outb(reg, 0x70);
    value = inb(0x71);
    __asm__("sti");
    return value;
}

void convert_timeZone(struct rtclock pclock, int offset, char option)
{
    unsigned int hour = (int)pclock.hour;
    clock_local.second = pclock.second;
    clock_local.minute = pclock.minute;
    if (option == '-')
    {
        int diffHour = (hour - offset);
        if (diffHour < 0)
        {
            clock_local.hour = 24 + diffHour;
            int diffDay = ((int)pclock.day - ((int)(diffHour / 24) + 1));
            if (diffDay < 1)
            {
                clock_local.day = 30 - ((int)(diffHour / 24) + 1);
                int diffMonth = ((int)pclock.month - ((int)(diffDay / 30) + 1));
                if (diffDay < 1)
                {
                    clock_local.month = 12 - ((int)(diffMonth / 12) + 1);
                    int diffYear = ((int)pclock.year - ((int)(diffMonth / 12) + 1));
                    clock_local.year = diffYear;
                }
                else
                {
                    clock_local.month = diffMonth;
                    clock_local.year = pclock.year;
                }
            }
            else
            {
                clock_local.day = diffDay;
                clock_local.month = pclock.month;
                clock_local.year = pclock.year;
            }
        }
        else
        {
            clock_local.hour = diffHour;
            clock_local.day = pclock.day;
            clock_local.month = pclock.month;
            clock_local.year = pclock.year;
        }
    }

    printf("TIME LOCAL=%d/%d/%d %d:%d:%d (%c%d)\n", clock_local.day, clock_local.month, clock_local.year, clock_local.hour, clock_local.minute, clock_local.second, option, offset);
}

void update_clock()
{
    clock.second = read_CMOS(BIT_SECOND);
    clock.minute = read_CMOS(BIT_MINUTE);
    clock.hour = read_CMOS(BIT_HOUR);
    clock.day = read_CMOS(BIT_DAY);
    clock.month = read_CMOS(BIT_MONTH);
    clock.year = read_CMOS(BIT_YEAR);
    unsigned int century = read_CMOS(BIT_CENTURY);

    if (!clock.is_binary)
    {
        clock.second = BCD_TO_BIN(clock.second);
        clock.minute = BCD_TO_BIN(clock.minute);
        clock.hour = BCD_TO_BIN(clock.hour);
        clock.day = BCD_TO_BIN(clock.day);
        clock.month = BCD_TO_BIN(clock.month);
        clock.year = BCD_TO_BIN(clock.year);
        century = BCD_TO_BIN(century);
    }

    clock.year = (century * 100) + clock.year;
    convert_timeZone(clock, 6, '-');
    printf("TIME HARDWARD=%d/%d/%d %d:%d:%d\n", clock.day, clock.month, clock.year, clock.hour, clock.minute, clock.second);
}

void init_rtclock()
{
    printf("####### RTCLOCK ########\n");
    unsigned char regB = read_CMOS(BIT_REGB);
    clock.is_24 = (regB & 0x2) != 0;
    clock.is_binary = (regB & 0x4) != 0;
    update_clock();
}

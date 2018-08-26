#include <stdint.h>

#include "display.h"
#include "rtc.h"

void clock(void);
uint8_t to_12_hour(uint8_t hour);

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    clock();
    return 0;
}

void clock(void)
{
    display_init();
    rtc_init();
    display_show(0, 0);
    for (;;) {
        rtc_time_t t = rtc_query_time();
        display_show(to_12_hour(t.hour), t.minute);
        rtc_wait_for_tick();
    }
}

uint8_t to_12_hour(uint8_t hour)
{
    uint8_t hour12 = hour % 12;
    return hour12 == 0 ? 12 : hour12;
}

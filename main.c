#include <stdint.h>

#include "display.h"
#include "rtc.h"

void clock(void);

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
        display_show(t.hour, t.minute);
        rtc_wait_for_tick();
    }
}

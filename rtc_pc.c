#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "rtc.h"

void rtc_init(void)
{
}

rtc_time_t rtc_query_time(void)
{
    time_t now;
    struct tm *now_struct;
    rtc_time_t result;
    time(&now);
    now_struct = localtime(&now);
    result.hour = now_struct->tm_hour;
    result.minute = now_struct->tm_min;
    return result;
}

void rtc_wait_for_tick(void)
{
    static int count = 0;
    count++;
    if (count == 3) {
        exit(0);
    }
    sleep(1);
}

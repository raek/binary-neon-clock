#include <util/delay.h>

#include "rtc.h"

static uint8_t rtc_hour;
static uint8_t rtc_minute;

void rtc_init(void)
{
    rtc_hour = 0;
    rtc_minute = 0;
}

rtc_time_t rtc_query_time(void)
{
    rtc_time_t result;
    result.hour = rtc_hour;
    result.minute = rtc_minute;
    return result;
}

void rtc_wait_for_tick(void)
{
    _delay_ms(1000);
    if (++rtc_minute < 60) {
        return;
    }
    rtc_minute = 0;
    if (++rtc_hour < 24) {
        return;
    }
    rtc_hour = 0;
}

#ifndef RTC_H
#define RTC_H

#include <stdint.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
} rtc_time_t;

void rtc_init(void);
rtc_time_t rtc_query_time(void);
void rtc_wait_for_tick(void);

#endif

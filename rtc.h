#ifndef RTC_H
#define RTC_H

#include <stdint.h>

typedef struct {
    uint8_t hour;   /* 1-12 */
    uint8_t minute; /* 0-59 */
} rtc_time_t;

void rtc_init(void);
rtc_time_t rtc_query_time(void);
void rtc_wait_for_tick(void);

#endif

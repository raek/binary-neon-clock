#include "i2c.h"
#include "intpin.h"
#include "rtc.h"
#include "serial.h"

#define RTC_I2C_ADDR (0x68)

static uint8_t from_bcd(uint8_t x);

void rtc_init(void)
{
    i2c_init();
    intpin_init();
    serial_init();
}

rtc_time_t rtc_query_time(void)
{
    uint8_t offset;
    uint8_t data[2];
    rtc_time_t result;
    offset = 0x01;
    i2c_write(RTC_I2C_ADDR, 1, &offset);
    i2c_read(RTC_I2C_ADDR, 2, data);
    result.minute = from_bcd(data[0]);
    result.hour = from_bcd(data[1] & 0x1F);
    serial_putc('0' + ((data[1] & 0x10) >> 4));
    serial_putc('0' + (data[1] & 0x0F));
    serial_putc(':');
    serial_putc('0' + (data[0] >> 4));
    serial_putc('0' + (data[0] & 0x0F));
    serial_putc('\r');
    serial_putc('\n');
    serial_putc('\r');
    serial_putc('\n');
    return result;
}

void rtc_wait_for_tick(void)
{
    intpin_wait_for_interrupt();
}

static uint8_t from_bcd(uint8_t x)
{
    return ((x>>4) & 0x0F) * 10 + (x & 0xF);
}

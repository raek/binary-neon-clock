#include <time.h>

#include "i2c.h"
#include "panic.h"

#define MEMORY_SIZE (0x12)
#define MY_ADDRESS (0x68)

static uint8_t memory[MEMORY_SIZE];
static uint8_t cursor;

static void next(void);
static void fill(void);
static uint8_t to_bcd(uint8_t x);
static uint8_t pack_hour(uint8_t hour);

void i2c_init(void)
{
    uint16_t i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0;
    }
    cursor = 0;
    fill();
}

void i2c_read(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    if (addr != MY_ADDRESS) {
        panic("Wrong I2C address");
    }
    fill();
    for (i = 0; i < len; i++) {
        data[i] = memory[cursor];
        next();
    }
}

void i2c_write(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    if (addr != MY_ADDRESS) {
        panic("Wrong I2C address");
    }
    fill();
    if (len >= 1) {
        cursor = data[0];
    }
    for (i = 1; i < len; i++) {
        memory[cursor] = data[i];
        next();
    }
}

static void next(void)
{
    cursor++;
    if (cursor >= MEMORY_SIZE) {
        cursor = 0;
        fill();
    }
}

static void fill(void)
{
    time_t now;
    struct tm *now_struct;
    time(&now);
    now_struct = localtime(&now);
    memory[1] = to_bcd(now_struct->tm_min);
    memory[2] = pack_hour(now_struct->tm_hour);
}

static uint8_t to_bcd(uint8_t x)
{
    return ((x/10)<<4) | (x%10);
}

static uint8_t pack_hour(uint8_t hour)
{
    uint8_t hour_part = hour % 12;
    uint8_t am_pm_part = 0x00;
    if (hour_part == 0) {
        hour_part = 12;
    }
    if (hour >= 12) {
        am_pm_part = 0x20;
    }
    return am_pm_part | to_bcd(hour_part);
}
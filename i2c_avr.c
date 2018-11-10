#include "i2c.h"

#define MEMORY_SIZE (0x12)

static uint8_t hour;
static uint8_t minute;
static uint8_t memory[MEMORY_SIZE];
static uint8_t cursor;

static void next(void);
static void update(void);
static void fill(void);
static uint8_t to_bcd(uint8_t x);
static uint8_t pack_hour(uint8_t hour);

void i2c_init(void)
{
    hour = 12;
    minute = 0;
}

void i2c_read(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    (void) addr;
    for (i = 0; i < len; i++) {
        data[i] = memory[cursor];
        next();
    }
}

void i2c_write(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    (void) addr;
    (void) data;
    update();
    fill();
    if (len >= 1) {
        cursor = data[0];
    }
    for (i = 1; i < len; i++) {
        next();
    }
}

static void next(void)
{
    cursor++;
    if (cursor >= MEMORY_SIZE) {
        cursor = 0;
    }
}

static void update(void)
{
    if (++minute < 60) {
        return;
    }
    minute = 0;
    if (++hour < 13) {
        return;
    }
    hour = 1;
}

static void fill(void)
{
    memory[1] = to_bcd(minute);
    memory[2] = pack_hour(hour);
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
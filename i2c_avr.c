#include <avr/io.h>

#define WRITE (0x00)
#define READ (0x01)

#include "i2c.h"
#include "panic.h"
#include "serial.h"

static void i2c_step(uint8_t flags);
static uint8_t i2c_wait(void);

void i2c_init(void)
{
    TWBR = ((F_CPU / 100000UL) - 16UL) / 2UL;
    TWCR = ((0<<TWINT) |
            (0<<TWEA) |
            (0<<TWSTA) |
            (0<<TWSTO) |
            (0<<TWWC) |
            (1<<TWEN) |
            (0<<TWIE));
    TWSR = ((0<<TWPS1) |
            (0<<TWPS0));
}

void i2c_read(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    i2c_step(1<<TWSTA);
    if (i2c_wait() != 0x08) {
        panic("i2c_read start");
    }
    TWDR = (addr<<1) | READ;
    i2c_step(0);
    if (i2c_wait() != 0x40) {
        i2c_step(1<<TWSTO);
        panic("i2c_read addr ack");
    }
    if (len == 0) {
        i2c_step(1<<TWSTO);
        return;
    }
    for (i = 0; i < (len - 1); i++) {
        i2c_step(1<<TWEA);
        if (i2c_wait() != 0x50) {
            i2c_step(1<<TWSTO);
            panic("i2c_read data ack");
        }
        data[i] = TWDR;
    }
    i2c_step(0);
    if (i2c_wait() != 0x58) {
        i2c_step(1<<TWSTO);
        panic("i2c_read last data ack");
    }
    data[len - 1] = TWDR;
    i2c_step(1<<TWSTO);
}

void i2c_write(uint8_t addr, uint16_t len, uint8_t *data)
{
    uint16_t i;
    i2c_step(1<<TWSTA);
    if (i2c_wait() != 0x08) {
        panic("i2c_write start");
    }
    TWDR = (addr<<1) | WRITE;
    i2c_step(0);
    if (i2c_wait() != 0x18) {
        i2c_step(1<<TWSTO);
        panic("i2c_write addr ack");
    }
    for (i = 0; i < len; i++) {
        TWDR = data[i];
        i2c_step(0);
        if (i2c_wait() != 0x28) {
            i2c_step(1<<TWSTO);
            panic("i2c_write data ack");
        }
    }
    i2c_step(1<<TWSTO);
}

static void i2c_step(uint8_t flags) {
    TWCR = (1<<TWINT) | (1<<TWEN) | flags;
}

static uint8_t i2c_wait(void)
{
    while (!(TWCR & (1<<TWINT))) {
    }
    return TWSR & 0xF8;
}
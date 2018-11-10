#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void i2c_init(void);
void i2c_read(uint8_t addr, uint16_t len, uint8_t *data);
void i2c_write(uint8_t addr, uint16_t len, uint8_t *data);

#endif
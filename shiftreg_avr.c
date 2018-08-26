#include <avr/io.h>

#include "shiftreg.h"

#define PC_SHCP (1<<2)
#define PC_STCP (1<<1)
#define PC_DATA (1<<0)

void shiftreg_init(void)
{
    DDRC |= PC_SHCP | PC_STCP | PC_DATA;
    PORTC &= ~(PC_SHCP | PC_STCP | PC_DATA);
}

void shiftreg_write(uint16_t bits)
{
    uint8_t i;

    for (i = 0; i < 16; i++) {
        if (bits & 0x8000) {
            PORTC |= PC_DATA;
        } else {
            PORTC &= ~PC_DATA;
        }
        bits <<= 1;
        PORTC |= PC_SHCP;
        PORTC &= ~PC_SHCP;
    }
    PORTC |= PC_STCP;
    PORTC &= ~PC_STCP;
}

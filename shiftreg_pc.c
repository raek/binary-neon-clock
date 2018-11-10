#include <stdio.h>

#include "shiftreg.h"

void shiftreg_init(void)
{
    puts("fedcba9876543210");
}

void shiftreg_write(uint16_t bits)
{
    uint8_t i;

    for (i = 0; i < 16; i++) {
        if (bits & 0x8000) {
            putchar('1');
        } else {
            putchar('0');
        }
        bits <<= 1;
    }
    putchar('\n');
    putchar('\n');
}

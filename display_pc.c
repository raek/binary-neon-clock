#include <stdio.h>

#include "display.h"

void display_init(void)
{
}

void display_show(uint8_t top, uint8_t bottom)
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        putchar(' ');
        top <<= 1;
    }
    for (i = 0; i < 4; i++) {
        putchar(top & 0x80 ? '1' : '0');
        top <<= 1;
    }
    putchar('\n');
    for (i = 0; i < 2; i++) {
        putchar(' ');
        bottom <<= 1;
    }
    for (i = 0; i < 6; i++) {
        putchar(bottom & 0x80 ? '1' : '0');
        bottom <<= 1;
    }
    putchar('\n');
    putchar('\n');
}


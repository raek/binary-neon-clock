#include "display.h"
#include "serial.h"
#include "shiftreg.h"

static void show_on_serial(uint8_t top, uint8_t bottom);

void display_init(void)
{
    serial_init();
    shiftreg_init();
}

void display_show(uint8_t top, uint8_t bottom)
{
    show_on_serial(top, bottom);
    shiftreg_write((((uint16_t) top) << 8) | ((uint16_t) bottom));
}

static void show_on_serial(uint8_t top, uint8_t bottom)
{
    uint8_t i;

    for (i = 0; i < 4; i++) {
        serial_putc(' ');
        top <<= 1;
    }
    for (i = 0; i < 4; i++) {
        serial_putc(top & 0x80 ? '1' : '0');
        top <<= 1;
    }
    serial_putc('\r');
    serial_putc('\n');
    for (i = 0; i < 2; i++) {
        serial_putc(' ');
        bottom <<= 1;
    }
    for (i = 0; i < 6; i++) {
        serial_putc(bottom & 0x80 ? '1' : '0');
        bottom <<= 1;
    }
    serial_putc('\r');
    serial_putc('\n');
    serial_putc('\r');
    serial_putc('\n');
}
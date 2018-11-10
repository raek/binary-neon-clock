#include "panic.h"
#include "serial.h"

void panic(char *message)
{
    char *p = message;
    serial_putc('\r');
    serial_putc('\n');
    while (*p != '\0') {
        serial_putc(*p);
        p++;
    }
    serial_putc('\r');
    serial_putc('\n');
    while (1) {
    }
}
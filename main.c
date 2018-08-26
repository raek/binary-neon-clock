#include <stdint.h>

#ifndef __AVR
#include <unistd.h>
#else
#include <util/delay.h>
#endif

#include "display.h"

int main(int argc, char** argv)
{
    uint16_t i = 0;
    
    (void) argc;
    (void) argv;
    display_init();
    for (;;) {
        display_show(i, i);
        #ifdef __AVR__
        _delay_ms(100);
        #else
        sleep(1);
        #endif
        i++;
        i %= 64;
    }
    return 0;
}

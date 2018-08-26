#include "display.h"
#include "shiftreg.h"

void display_init(void)
{
    shiftreg_init();
}

void display_show(uint8_t top, uint8_t bottom)
{
    shiftreg_write((((uint16_t) top) << 8) | ((uint16_t) bottom));
}

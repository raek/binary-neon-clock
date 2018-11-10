#include <stdlib.h>
#include <unistd.h>

#include "intpin.h"

void intpin_init(void)
{
}

void intpin_wait_for_interrupt(void)
{
    static int count = 0;
    count++;
    if (count == 3) {
        exit(0);
    }
    sleep(1);
}
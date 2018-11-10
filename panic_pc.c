#include <stdio.h>
#include <stdlib.h>

#include "panic.h"

void panic(char *message)
{
    puts(message);
    putchar('\n');
    exit(1);
}
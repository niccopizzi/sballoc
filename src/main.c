#include "sballoc.h"

void* malloc(size_t size)
{
    (void)size;
    write(1, "Hello\n", 6);
    return (0);
}
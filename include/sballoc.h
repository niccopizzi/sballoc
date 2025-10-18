#ifndef SBALLOC_H
#define SBALLOC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);

void    show_alloc_mem();
#endif
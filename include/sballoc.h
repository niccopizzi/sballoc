#ifndef SBALLOC_H
#define SBALLOC_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/mman.h>
#include <assert.h>


#define IN_USE_FLAG     1
#define MMAPED_FLAG     1 << 1
#define UNUSED_FLAG     1 << 2

#define KILOBYTE 1024
#define MEGABYTE KILOBYTE * KILOBYTE

#define TINY_SBAL   124
#define SMALL_SBAL  1024

#define TINY_MMAP_ARGS NULL, TINY_SBAL * 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0

#define SMALL_MMAP_ARGS NULL, TINY_SBAL * 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0

typedef struct s_chunk
{
    size_t      chunk_size;
    void*       user_data;
    size_t      prev_chunk_sz;
} sballoc_chunk;

typedef sballoc_chunk* sblcnkptr; 

typedef struct s_arena
{
    void*              heap_start;
    sblcnkptr          tiny_sbal_start;
    sblcnkptr          small_sbal_start;
} sballoc_arena;

/*Main arena of the program, we start everything from here*/
sballoc_arena   the_arena;

void    sballoc_free(void *ptr);
void    *sballoc(size_t size);
void    *resballoc(void *ptr, size_t size);

void    show_alloc_mem();

#endif
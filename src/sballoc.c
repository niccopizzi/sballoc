#include "sballoc.h"

void smemset(void* ptr, int n, size_t bytes)
{
    for (size_t i = 0; i < bytes; ++i)
    {
        printf("Setting memory for byte %ld\n", i);
        *(char *)ptr = n;
    }
}

static void sballoc_init()
{
    the_arena.tiny_sbal_start = mmap(TINY_MMAP_ARGS);

    assert(the_arena.tiny_sbal_start != MAP_FAILED);

    smemset(the_arena.tiny_sbal_start, 0, 102399);
    
    /* the_arena.small_sbal_start = mmap(SMALL_MMAP_ARGS);

    assert(the_arena.small_sbal_start != MAP_FAILED);

    smemset(the_arena.small_sbal_start, 0, SMALL_SBAL * 100);
 */
}

sblcnkptr sballoc_big_chunk(size_t size)
{
    sblcnkptr the_chunk = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (the_chunk == MAP_FAILED)
        return (NULL);
    the_chunk->chunk_size = size | IN_USE_FLAG | MMAPED_FLAG;
    return (the_chunk);
}

bool is_chunk_free(sblcnkptr chunk)
{
    return ((chunk->chunk_size & IN_USE_FLAG) == 0);
}

sblcnkptr sballoc_new_chunk(size_t size)
{
    sblcnkptr chunk;
    
    switch (size)
    {
    case TINY_SBAL:
        chunk = the_arena.tiny_sbal_start;
        break;
    case SMALL_SBAL:
        chunk = the_arena.small_sbal_start;
        break;
    default:
        return (sballoc_big_chunk(size));
    }

    for (int i = 0; i < 100; ++i)
    {
        if (is_chunk_free(chunk + i))
        {
            printf("Found free chunk at address %p\n", chunk + i);
            (chunk + i)->chunk_size = size | IN_USE_FLAG;
            return (chunk + i);
        }
    }
    return (NULL);
}

void* sballoc(size_t size)
{
    if (the_arena.small_sbal_start == NULL)
        sballoc_init();
    
    sblcnkptr ret_chunk = sballoc_new_chunk(size);

    return ((ret_chunk == NULL ? NULL : ret_chunk->user_data));
}
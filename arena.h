#ifndef __ARENA_INCLUDED_H__
#define __ARENA_INCLUDED_H__

#include "arena_linear.h"
#include "arena_list.h"
#include "arena_pool.h"
#include <stddef.h>
#include <stdint.h>

#define SIZE_KB (1024)
#define SIZE_MB (SIZE_KB * 1024)
#define SIZE_GB (SIZE_MB * 1024)

struct arena {
  uint8_t *buffer;
  size_t size;
  size_t offset;
};

/*
 * initialize a new arena from aligned memory block
 * memory: aligned memory block
 * size: memory block size
 * offset: memory block offset
 * arena_size: size of the new arena
 */
struct arena arena_init(void *memory, size_t size, size_t offset,
                        size_t arena_size);

/*
 * reset data of arena
 */
void arena_reset(struct arena *arena);

struct arena_linear arena_linear_alloc(struct arena *arena, int count,
                                       uint32_t size);

struct arena_pool arena_pool_alloc(struct arena *arena, int count,
                                   uint32_t size);

struct arena_list arena_list_alloc(struct arena *arena, uint32_t size);

#endif // __ARENA_INCLUDED_H__

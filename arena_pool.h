#ifndef __ARENA_POOL_INCLUDED_H__
#define __ARENA_POOL_INCLUDED_H__

#include "common.h"
#include <stddef.h>
#include <stdint.h>

/*
 * arena pool data structure
 */
struct arena_pool {
  /* arena pool memory */
  uint8_t *buffer;

  /* arena pool size */
  uint32_t size;

  /* arena data size */
  uint32_t blk_size;

  /* ring buffer to store released indexes */
  uint32_t *blk_free;

  /* ring buffer head index */
  uint32_t blk_head;

  /* ring buffer tail index */
  uint32_t blk_tail;
};

#define arena_pool_push_data(arena, type)                                      \
  __arena_push_data_internal(arena_pool_push, (arena), sizeof(type))

#define arena_pool_push_array(arena, type, size)                               \
  __arena_push_array_internal(arena_pool_push, (arena), size * sizeof(type))

void *arena_pool_push(struct arena_pool *arena, size_t size);

void arena_pool_reset(struct arena_pool *arena);

#endif // __ARENA_POOL_INCLUDED_H__

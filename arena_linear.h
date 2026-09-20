#ifndef __ARENA_LINEAR_INCLUDED_H__
#define __ARENA_LINEAR_INCLUDED_H__

#include "common.h"
#include <stddef.h>
#include <stdint.h>

struct arena_linear {
  uint8_t *buffer;
  uint32_t size;
  uint32_t offset;
};

#define arena_linear_push_data(arena, type)                                    \
  __arena_push_data_internal(arena_linear_push, (arena), sizeof(type))

#define arena_linear_push_array(arena, type, size)                             \
  __arena_push_array_internal(arena_linear_push, (arena), size * sizeof(type))

void *arena_linear_push(struct arena_linear *arena, size_t size);

void arena_linear_reset(struct arena_linear *arena);

#endif // __ARENA_LINEAR_INCLUDED_H__

#ifndef __ARENA_LIST_INCLUDED_H__
#define __ARENA_LIST_INCLUDED_H__

#include "common.h"
#include <stddef.h>
#include <stdint.h>

struct arena_list {
  uint8_t *buffer;
  uint64_t size;
  uint64_t offset;
};

#define arena_list_push_data(arena, type)                                      \
  __arena_push_data_internal(arena_list_push, (arena), sizeof(type))

#define arena_list_push_array(arena, type, size)                               \
  __arena_push_array_internal(arena_list_push, (arena), size * sizeof(type))

void *arena_list_push(struct arena_list *arena, size_t size);

void arena_list_reset(struct arena_list *arena);

#endif // __ARENA_LIST_INCLUDED_H__

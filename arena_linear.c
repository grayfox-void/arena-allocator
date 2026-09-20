#include "arena_linear.h"
#include "debug.h"

void *arena_linear_push(struct arena_linear *arena, size_t size) {
  void *ptr = NULL;

  dbg_assert(arena->size - arena->offset > size);

  if (size > arena->size - arena->offset)
    return NULL;

  ptr = arena->buffer + arena->offset;
  arena->offset += size;

  return ptr;
}

void arena_linear_reset(struct arena_linear *arena) {
  dbg_assert(arena);

  if (arena)
    arena->offset = 0;
}

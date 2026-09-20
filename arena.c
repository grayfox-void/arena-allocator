#include "arena.h"
#include "debug.h"

#define BLOCK_FREE_SIZE 1024

struct arena arena_init(void *memory, size_t size, size_t offset,
                        size_t arena_size) {
  struct arena _arena = {0};
  size_t _size = size - offset;

  dbg_assert(_size >= arena_size);

  if (_size >= arena_size) {
    _arena.buffer = memory + offset;
    _arena.size = arena_size;
    _arena.offset = 0;
  } else {
    _arena.buffer = NULL;
    _arena.size = 0;
    _arena.offset = 0;
  }

  return _arena;
}

void arena_reset(struct arena *arena) {
  if (arena)
    arena->offset = 0;
}

struct arena_linear arena_linear_alloc(struct arena *arena, int count,
                                       uint32_t size) {
  struct arena_linear _arena_linear = {0};
  uint32_t arena_size = count * size;

  if (arena_size > arena->size - arena->offset) {
    _arena_linear.buffer = NULL;
    _arena_linear.size = 0;
    _arena_linear.offset = 0;
  } else {
    _arena_linear.buffer = arena->buffer + arena->offset;
    _arena_linear.size = arena_size;
    _arena_linear.offset = 0;

    arena->offset += _arena_linear.size;
  }

  return _arena_linear;
}

struct arena_pool arena_pool_alloc(struct arena *arena, int count,
                                   uint32_t size) {
  struct arena_pool _arena_pool = {0};
  uint32_t arena_size = count * size + BLOCK_FREE_SIZE;

  if (arena_size > arena->size - arena->offset) {
    _arena_pool.buffer = NULL;
    _arena_pool.size = 0;
    _arena_pool.blk_size = 0;
    _arena_pool.blk_free = NULL;
    _arena_pool.blk_head = 0;
    _arena_pool.blk_tail = 0;
  } else {
    _arena_pool.buffer = arena->buffer + arena->offset;
    _arena_pool.size = arena_size;
    _arena_pool.blk_size = size;
    _arena_pool.blk_free = (uint32_t *)_arena_pool.buffer + arena_size;
    _arena_pool.blk_head = 0;
    _arena_pool.blk_tail = 0;

    arena->offset += _arena_pool.size;
  }

  return _arena_pool;
}

struct arena_list arena_list_alloc(struct arena *arena, uint32_t size) {
  struct arena_list _arena_list = {0};

  return _arena_list;
}

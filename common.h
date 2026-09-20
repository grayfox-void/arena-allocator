#ifndef __ARENA_COMMON_INCLUDED_H__
#define __ARENA_COMMON_INCLUDED_H__

#define __arena_push_data_internal(arena_func, arena, type)                    \
  (type *)arena_func((arena), sizeof(type))

#define __arena_push_array_internal(arena_func, arena, type, size)             \
  (type *)arena_func((arena), size * sizeof(type))

#endif // __ARENA_COMMON_INCLUDED_H__

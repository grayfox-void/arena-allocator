#ifndef __DEBUG_INCLUDED_H__
#define __DEBUG_INCLUDED_H__

#if defined ENABLE_ASSERTS

#include <stdio.h>

#if defined(_MSC_VER)
#define dbg_break() __debugbreak()
#else
#define dbg_break() __builtin_trap()
#endif

#define dbg_assert(condition)                                                  \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "ASSERT FAILED: %s failed in %s:%d\n", #condition,       \
              __FILE__, __LINE__);                                             \
      fflush(stderr);                                                          \
      dbg_break();                                                             \
    }                                                                          \
  } while (0)

#else
#define dbg_assert(condition)
#endif

#endif // __DEBUG_INCLUDED_H__

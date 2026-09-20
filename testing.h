#ifndef __TESTING_INCLUDED_H__
#define __TESTING_INCLUDED_H__

#if defined ENABLE_TESTING

#include <stdatomic.h>
#include <stdio.h>
#include <string.h>

extern atomic_int g_assert_success;
extern atomic_int g_assert_failure;

#define test_suite(name) fprintf(stdout, "\n[SUITE]: %s\n", name)

#define test_assert(condition)                                                 \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, " [ERROR]: [%s] in function [%s] file [%s] line [%d]\n", \
              #condition, __FUNCTION__, __FILE__, __LINE__);                   \
      fflush(stderr);                                                          \
      atomic_fetch_add(&g_assert_failure, 1);                                  \
    } else {                                                                   \
      fprintf(stderr,                                                          \
              " [SUCCESS]: [%s] in function [%s] file [%s] line [%d]\n",       \
              #condition, __FUNCTION__, __FILE__, __LINE__);                   \
      fflush(stdout);                                                          \
      atomic_fetch_add(&g_assert_success, 1);                                  \
    }                                                                          \
  } while (0)

#define test_success()                                                         \
  do {                                                                         \
    int _g_assert_success = atomic_load(&g_assert_success);                    \
    fprintf(stdout, "TEST SUCCESS: %d\n", _g_assert_success);                  \
  } while (0)

#define test_failure()                                                         \
  do {                                                                         \
    int _g_assert_failure = atomic_load(&g_assert_failure);                    \
    fprintf(stdout, "TEST FAILURE: %d\n", _g_assert_failure);                  \
  } while (0)

#define test_total()                                                           \
  do {                                                                         \
    int _g_assert_success = atomic_load(&g_assert_success);                    \
    int _g_assert_failure = atomic_load(&g_assert_failure);                    \
    fprintf(stdout, "TEST TOTAL: %d\n",                                        \
            _g_assert_success + _g_assert_failure);                            \
  } while (0)

#else

#define test_suite(name)
#define test_assert(condition)
#define test_success()
#define test_failure()
#define test_total()

#endif

#endif // __TESTING_INCLUDED_H__

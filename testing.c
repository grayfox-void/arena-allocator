#include "testing.h"

#ifdef ENABLE_TESTING

atomic_int g_assert_success = 0;
atomic_int g_assert_failure = 0;

_Atomic char *test_name = NULL;

#endif

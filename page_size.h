#ifndef __MEMALLOC_PAGE_SIZE_H_INCLUDED__
#define __MEMALLOC_PAGE_SIZE_H_INCLUDED__

#if defined(__linux__) || defined(__gnu_linux__) || defined(__FreeBSD__)
#include <sys/user.h>
#include <unistd.h>

#if defined(PAGE_SIZE)
#define MEMALLOC_PAGE_SIZE PAGE_SIZE
#elif defined(EXEC_PAGESIZE)
#define MEMALLOC_PAGE_SIZE EXEC_PAGESIZE
#else
#define MEMALLOC_PAGE_SIZE (sysconf(_SC_PAGESIZE))
#endif

#elif defined(_WIN32) || defined(_WIN64)
#if defined(_M_MRX000) || defined(_M_MIPS)
#define MEMALLOC_PAGE_SIZE 2048
#else
#define MEMALLOC_PAGE_SIZE 4096
#endif

#elif defined(__APPLE__) && defined(__MACH__)
#if defined(__arm64__) || defined(__aarch64__)
#define MEMALLOC_PAGE_SIZE 16384
#else
#define MEMALLOC_PAGE_SIZE 4096
#endif

#else
#if defined(__mips__) || defined(__sh__) || defined(_MIPS_ISA)
#define MEMALLOC_PAGE_SIZE 2048
#else
#define MEMALLOC_PAGE_SIZE 4096
#endif
#endif

#define MEMALLOC_CACHE_LINE_SIZE 64

#define MEMALLOC_PAGE_ALIGN(size)                                              \
  (((size) + (MEMALLOC_PAGE_SIZE - 1)) & ~(MEMALLOC_PAGE_SIZE - 1))

#define MEMALLOC_CACHE_ALIGN(size)                                             \
  (((size) + (MEMALLOC_CACHE_LINE_SIZE - 1)) & ~(MEMALLOC_CACHE_LINE_SIZE - 1))

#endif /* __MEMALLOC_PAGE_SIZE_H_INCLUDED__ */

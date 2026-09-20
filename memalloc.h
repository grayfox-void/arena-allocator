#ifndef __MEMALLOC_H_INCLUDED__
#define __MEMALLOC_H_INCLUDED__

#include "page_size.h"
#include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <malloc.h>
#define ma_aligned_alloc(alignment, size) _aligned_malloc((size), (alignment))
#define ma_aligned_free(ptr) _aligned_free((ptr))

#elif defined(__linux__) || defined(__gnu_linux__) || defined(__FreeBSD__)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
static inline void *ma_aligned_alloc(size_t alignment, size_t size)
{
	size_t aligned_size = (size + (alignment - 1)) & ~(alignment - 1);
	return aligned_alloc(alignment, aligned_size);
}
#define ma_aligned_free(ptr) free((ptr))
#else
/* Old Linux/POSIX fallback without C11 (posix_memalign) */
static inline void *ma_aligned_alloc(size_t alignment, size_t size)
{
	void *ptr = NULL;
	if (posix_memalign(&ptr, alignment, size) != 0)
		return NULL;
	return ptr;
}
#define ma_aligned_free(ptr) free((ptr))
#endif

#else
static inline void *ma_aligned_alloc(size_t alignment, size_t size)
{
	void *raw_ptr = malloc(size + alignment + sizeof(void *));
	if (!raw_ptr)
		return NULL;

	uintptr_t raw_addr = (uintptr_t)raw_ptr + sizeof(void *);
	uintptr_t aligned_addr = (raw_addr + (alignment - 1)) &
				 ~(alignment - 1);

	void **meta_space = (void **)(aligned_addr - sizeof(void *));
	*meta_space = raw_ptr;

	return (void *)aligned_addr;
}

static inline void ma_aligned_free(void *ptr)
{
	if (!ptr)
		return;

	void **meta_space = (void **)((uintptr_t)ptr - sizeof(void *));
	free(*meta_space);
}
#endif

#endif /* __MEMALLOC_H_INCLUDED__ */

#include "arena.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE (SIZE_MB * 4)
#define ARENA_STATIC_SIZE (MEMORY_SIZE * 0.5f)
#define ARENA_TEMP_SIZE (MEMORY_SIZE * 0.5f)

/* test: allocate a block of memory aligned to OS pages */
void test_memory_alignment(void)
{
	void *memory = aligned_alloc(4096, MEMORY_SIZE);
	test_assert(memory != NULL);

	if (!memory)
		return;

	test_assert((size_t)memory % 4096 == 0);

	free(memory);
}

/* test: create an arena of the same size of the allocated memory */
void test_create_arena_equal_to_memory_size_success(void)
{
	void *memory = aligned_alloc(4096, MEMORY_SIZE);
	test_assert(memory != NULL);

	if (!memory)
		return;

	struct arena static_arena =
		arena_init(memory, MEMORY_SIZE, 0, MEMORY_SIZE);

	test_assert(static_arena.size == MEMORY_SIZE);

	free(memory);
}

void test_create_two_arenas_success(void)
{
	void *memory = aligned_alloc(4096, MEMORY_SIZE);
	test_assert(memory != NULL);

	if (!memory)
		return;

	struct arena static_arena =
		arena_init(memory, MEMORY_SIZE, 0, ARENA_STATIC_SIZE);
	if (!static_arena.buffer)
		goto err;

	test_assert(static_arena.size == SIZE_MB * 2);

	struct arena temp_arena = arena_init(
		memory, MEMORY_SIZE, ARENA_STATIC_SIZE, ARENA_TEMP_SIZE);
	if (!temp_arena.buffer)
		goto err;

	test_assert(temp_arena.size == SIZE_MB * 2);

err:
	free(memory);
}

void test_create_linear_arena_success(void)
{
	void *memory = aligned_alloc(4096, MEMORY_SIZE);
	test_assert(memory != NULL);

	if (!memory)
		return;

	struct arena static_arena =
		arena_init(memory, MEMORY_SIZE, 0, MEMORY_SIZE);

	test_assert(static_arena.size == MEMORY_SIZE);

	struct arena_linear linear_arena =
		arena_linear_alloc(&static_arena, 128, sizeof(unsigned long));

	test_assert(linear_arena.buffer != NULL);

	test_assert(linear_arena.size == 1024);

	free(memory);
}

void test_create_arena_failure(void)
{
	void *memory = aligned_alloc(4096, MEMORY_SIZE);
	test_assert(memory != NULL);

	if (!memory)
		return;

	struct arena static_arena =
		arena_init(memory, MEMORY_SIZE, 0, MEMORY_SIZE + 1);

	test_assert(static_arena.buffer == NULL);

	free(memory);
}

void test_create_arena_linear_success()
{
}

int main(void)
{
	test_suite("mem aligned to pages");
	test_memory_alignment();

	test_suite("arena creation");
	test_create_arena_equal_to_memory_size_success();
	test_create_two_arenas_success();
	test_create_arena_linear_success();
	test_create_linear_arena_success();

	test_create_arena_failure();

	test_success();
	test_failure();
	test_total();

	return 0;
}

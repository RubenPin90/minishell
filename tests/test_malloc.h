
// #ifndef TEST_MALLOC_H
// # define TEST_MALLOC_H
// # include <stdlib.h>

// # define malloc(s) (my_malloc(s))
// # define alloc_num 135

// static int i;
// static void *(*org_malloc)(size_t) = malloc;
// static void *my_malloc(size_t size) __attribute__((used));

// static void *my_malloc(size_t size)
// {
// 	if (i == alloc_num)
// 		return (NULL);
// 	i++;
// 	return (org_malloc(size));
// }

// #endif


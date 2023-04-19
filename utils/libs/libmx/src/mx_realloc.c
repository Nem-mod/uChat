#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
	if (ptr == NULL && size == 0)
		size = 1;
	if (size <= 0) {
		if (ptr != NULL)
			free(ptr);
		return NULL;
	}

	size_t ptr_size;
	#if __linux__
    	ptr_size = malloc_usable_size(ptr); 	// For Linux
	#elif __APPLE__
   		ptr_size = malloc_size(ptr);			// For MacOS
	#endif
	
	if (ptr_size > size)
		size = ptr_size;

	void *new = malloc(size);
	if (new == NULL)
		return NULL;

	if (ptr != NULL) {
		mx_memmove(new, ptr, size);
		free(ptr);
	}

	return new;
}

// int main() {
// 	size_t s1 = 100;
// 	size_t s2 = 0;
// 	int *a = malloc(s1);
// 	int *b = malloc(s1);
// 	// int *a = NULL;
// 	// int *b = NULL;

// 	printf("%lu || %lu\n", malloc_usable_size(a), malloc_usable_size(b));
// 	a = mx_realloc(a, s2);
// 	b = realloc(b, s2);
// 	printf("%lu || %lu\n", malloc_usable_size(a), malloc_usable_size(b));

// 	return 0;
// }

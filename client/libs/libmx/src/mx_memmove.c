#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
	char *buf = NULL;

	buf = malloc(len);
	//printf("dst = %lu\nsrc = %lu\nbuf = %lu\nlen = %zu\n\n", malloc_usable_size(dst), malloc_usable_size((void*)src), malloc_usable_size(buf), len);
	mx_memcpy(buf, src, len);
	mx_memcpy(dst, buf, len);
	free(buf);

	return dst;
}

// int main() {
//     char s1[] = "Hello world!";
//     char s2[25];

//     printf("%s\n%s\n\n", s1, s2);
//     mx_memmove(s2, s1, 7);
//     printf("%s\n%s\n\n", s1, s2);


//     return 0;
// }

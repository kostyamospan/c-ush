#include "../inc/libmx.h"

char *mx_str_size_cpy(char *dst, const char *src, int start, int end) {
	int i = 0;
	int j = start;

	while  (j < end) {
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return dst;
}

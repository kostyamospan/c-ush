#include "../inc/libmx.h"

char *mx_str_size_dup(const char *s1, size_t start, size_t end) {
	char *copy = NULL;

	copy = mx_strnew(end - start);
	if (copy  == NULL)
		return NULL;
	else
		mx_str_size_cpy(copy, s1, start, end);
	return copy;
}

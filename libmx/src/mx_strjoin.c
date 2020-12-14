#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
	if (s1 == 0 && s2 == 0) return 0;
	if (s1 == 0) return mx_strdup(s2);
	if (s2 == 0) return mx_strdup(s1);
	char *cat_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2) + 1);
	if (cat_str == 0) return 0;
	cat_str = mx_strcpy(cat_str, s1);
	cat_str = mx_strcat(cat_str, s2);
	return cat_str;
}

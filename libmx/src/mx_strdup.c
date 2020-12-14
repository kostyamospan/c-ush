#include "../inc/libmx.h"

char *mx_strdup(const char *str) {
    int len = mx_strlen(str) + 1;
    char *res = mx_strnew(len);
    if (res == (char*) 0) return (char*) 0;
    return (char*) mx_strcpy(res, str);
}

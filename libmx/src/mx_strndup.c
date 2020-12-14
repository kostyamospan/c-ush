#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n)
{
    size_t size = (int)mx_strlen(s1);
    if (size > n)
        size = n;
    char *result = mx_strnew((int)size);

    return (mx_strncpy(result, s1, (int)size));
}

#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL) return -2;
    int len = mx_strlen(str);
    for (int index = 0; index < len; index++)
        if (str[index] == c) return index;
    return -1;
}

#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL || mx_strlen(str) <= 0)
        return NULL;
    int size = mx_strlen(str);
    int space_1 = 0;
    int space_2 = 0;
    for (int i = 0; i < mx_strlen(str); i++) {
        if(mx_isspace(str[i]))
            space_1++;
        else
            break;
    }
    for (int i = mx_strlen(str)-1; i > space_1; i--) {
        if(mx_isspace(str[i]))
            space_2++;
        else
            break;
    }
    int new_size = size - (space_1 + space_2);
    char *result = mx_strnew(new_size);
    return mx_strncpy(result,&str[space_1],new_size);
}

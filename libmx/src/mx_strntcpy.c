#include "../inc/libmx.h"

char *mx_strntcpy(char *dest, const char *from, int f_p, int s_p)
{
    if (s_p < f_p || s_p < 0 || f_p >= mx_strlen(from) || f_p >= mx_strlen(from))
        return NULL;

    char *res_str = mx_strnew(s_p - f_p);

    int j = 0;

    for (int i = f_p; i < s_p; i++)
        res_str[j++] = from[i];

    dest = res_str;
    return res_str;
}


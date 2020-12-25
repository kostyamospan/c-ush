#include "../inc/ush.h"

char *mx_strconcant_new(const char *str1, const char *str2)
{
    int l1, l2;
    char *res = mx_strnew((l1 = mx_strlen(str1)) + (l2 = mx_strlen(str2)));

    int i = 0;

    for (; i < l1; i++)
        res[i] = str1[i];

    for (int j = 0; j < l2; j++, i++)
        res[i] = str2[j];

    return res;
}

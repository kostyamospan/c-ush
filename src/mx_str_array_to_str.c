#include "../inc/ush.h"

char *mx_str_arr_to_str(const char **arr, int argc)
{
    char *res;
    int l = 0;

    for (int i = 0; i < argc; i++)
        l += mx_strlen(arr[i]);

    res = mx_strnew(l + argc - 1);

    for (int i = 0; i < argc - 1; i++)
    {
        strcat(res, arr[i]);
        strcat(res, " ");
    }

    strcat(res, arr[argc - 1]);

    return res;
}
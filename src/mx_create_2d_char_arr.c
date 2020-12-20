#include "../inc/ush.h"

t_2d_arr *mx_create_2d_char_arr(void **arr, int size)
{
    t_2d_arr *res = malloc(sizeof(t_2d_arr));
    res->data = arr;
    res->size = size;
    return res;
}

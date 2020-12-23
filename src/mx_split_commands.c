#include "../inc/ush.h"

t_2d_arr *mx_split_commands(const char *arg)
{
    char **splitted_str = mx_str_split(mx_strdup(arg), ';');
    int str_count = 0;
    while (splitted_str[str_count] != NULL)
        str_count++;

    for (int i = 0; i < str_count; i++)
    {
        mx_replace_exp(splitted_str[i]);
    }

    return mx_create_2d_char_arr((void **)splitted_str, str_count);
}

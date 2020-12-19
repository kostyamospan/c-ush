#include "../inc/ush.h"

t_2d_arr *mx_parse_commands(t_2d_arr *commands)
{
    t_command **arr = malloc(sizeof(t_command) * commands->size);

    for (int i = 0; i < commands->size; i++)
    {
        arr[i] = mx_parse_str_command(((char **)(commands->data))[i]);
    }

    return mx_create_2d_char_arr((void **)arr, commands->size);
}

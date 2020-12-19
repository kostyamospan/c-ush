#include "../inc/ush.h"

t_command *mx_parse_str_command(char *command_str)
{
    char **str = mx_str_split(command_str, ' ');
    int count = 0;

    while (str[count] != NULL)
        count++;

    t_2d_arr *command = mx_create_2d_char_arr((void **)str, count);
    
    return mx_create_command(
        mx_strdup((const char *)(((char **)(command->data))[0])),
        (char **)(command->size > 1 ? &(command->data[1]) : NULL),
        command->size - 1);
}

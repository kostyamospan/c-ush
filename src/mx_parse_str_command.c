#include "../inc/ush.h"

t_command *mx_parse_str_command(char *command_str)
{
    char **str = mx_str_split(command_str, ' ');
    int count = 0;

    while (str[count] != NULL)
        count++;

    return mx_create_command(
        str,
        count);
}

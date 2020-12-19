#include "../inc/ush.h"

char **mx_command_to_array(t_command *command)
{
    char **arr = malloc(command->argc + 2 * sizeof(char *));
    memcpy((*arr + 1), command->args, (size_t)command->argc);
    arr[0] = command->name;
    return arr;
}

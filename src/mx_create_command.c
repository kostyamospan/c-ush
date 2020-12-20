#include "../inc/ush.h"

t_command *mx_create_command(char **args, int argc)
{
    t_command *res = malloc(sizeof(t_command));

    res->argswn = args;
    res->argc = argc - 1;
    res->name = args ? (argc ? args[0]
                             : NULL)
                     : NULL;

    if (argc >= 1)
        res->args = args ? &args[1] : NULL;

    return res;
}

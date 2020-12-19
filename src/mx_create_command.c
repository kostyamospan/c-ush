#include "../inc/ush.h"

t_command *mx_create_command(char *name, char **args, int argc)
{
    t_command *res = malloc(sizeof(t_command));
    res->argc = argc;
    res->args = args;
    res->name = name;
    return res;
}

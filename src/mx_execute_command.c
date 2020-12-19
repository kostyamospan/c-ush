#include "../inc/ush.h"

int mx_execute_command(char **args)
{
    int i;

    if (args[0] == NULL)
    {
        return 1;
    }

    for (i = 0; i < lsh_num_builtins(); i++)
        if (strcmp(args[0], builtins[i]) == 0)
            return (*builtins_funcs[i])(args);

    return lsh_launch(args);
}
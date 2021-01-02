#include "../inc/ush.h"

int mx_get_command_type(char *name)
{
    for (int i = 0; i < mx_builtins_count(builtins); i++)
        if (mx_strcmp((char *const)name, builtins[i]) == 0)
            return COMMAND_BUILTIN;

    return COMMAND_EXTERNAL;
}

#include "../inc/ush.h"

int mx_process_command(char *command_str)
{
    t_command *command = mx_parse_str_command(command_str);

    for (int i = 0; i < command->argc; i++)
    {
        mx_replace_exp(&(command->args[i]));
    }

    for (int i = 0; i < mx_builtins_count(); i++)
        if (strcmp(command->name, builtins[i]) == 0)
            return (*builtins_funcs[i])(command);

    return mx_launch_program(command->argswn);
}

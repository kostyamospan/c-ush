#include "../inc/ush.h"

int mx_process_command(char *command_str)
{
    t_command *command = mx_parse_str_command(command_str);

    for (int i = 0; i < mx_builtins_count(); i++)
        if (strcmp(command->name[0], builtins[i]) == 0)
            return (*builtins_funcs[i])(command->args);

    return mx_launch_program(mx_command_to_array(command));
}

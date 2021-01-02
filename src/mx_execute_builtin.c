#include "../inc/ush.h"

int ush_execute_builtin_command(t_process *proc)
{
    int status = 0;

    for (int i = 1; i < proc->argc; i++)
        mx_replace_exp(&(proc->argv[i]));

    for (int i = 0; i < mx_builtins_count(); i++)
    {
        if (mx_strcmp(proc->argv[0], builtins[i]) == 0)
        {
            builtins_funcs[i](proc);
            return 1;
        }
    }

    return 0; // status;
}

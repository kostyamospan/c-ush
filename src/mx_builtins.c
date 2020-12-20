#include "../inc/ush.h"

int mx_exit_builtin(t_command *command)
{
    return 0;
}

int mx_export_builtin(t_command *command)
{
    if (command->argc == 0)
    {
        for (char **env = environ; *env; ++env)
            printf("%s\n", *env);
    }
    else if (command->argc == 1)
    {
        printf("seting variable\n");
    }

    return 1;
}

int mx_pwd_builtin(t_command *command)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);

    return 1;
}

int mx_echo_builtin(t_command *command)
{
    // int not_flag_pos = 0;
    int i = 0;

    if (command->argc)
        while (mx_is_flag(command->args[i]) && i < command->argc)
            i++;

    if (i < command->argc)
    {
        for (int j = i; j < command->argc - 1; j++)
            printf("%s ", command->args[j]);

        printf("%s", command->args[command->argc - 1]);
    }

    if (!mx_is_arguments_contains_flag(command->args, command->argc, 'n'))
        printf("\n");

    return 1;
}

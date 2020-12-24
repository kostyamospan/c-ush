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
        for (int i = 0; i < command->argc; i++)
        {
            char **splitted_arg = mx_str_split(command->args[i], '=');

            if (splitted_arg != NULL)
            {
                setenv(splitted_arg[0], splitted_arg[1], 1);
            }

            free(splitted_arg);
        }
    }

    return 1;
}

int mx_unset_builtin(t_command *command)
{
    if (command->argc >= 1)
    {
        for (int i = 0; i < command->argc; i++)
            unset(command->args[i]);
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

int mx_cd_builtin(t_command *command)
{
    char *dir_name;

    if (command->args == NULL || command->args[0] == NULL)
    {
        dir_name = getenv("HOME");
        printf("%s", dir_name);
    }
    else
        dir_name = command->args[0];

    if (chdir((const char *)dir_name) != 0)
        perror("lsh");

    return 1;
}
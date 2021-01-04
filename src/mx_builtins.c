#include "../inc/ush.h"

int mx_exit_builtin(t_process *command)
{
    exit(0);
    return 0;
}
// #ifdef __USE_XOPEN2K

bool mx_sort_predicate(void *s1, void *s2)
{
    return mx_strcmp((char *)s1, (char *)s2) > 0;
}

int mx_export_builtin(t_process *command)
{
    if (command->argc == 1)
    {
        t_list *head = NULL;

        for (char **env = environ; *env; ++env)
            mx_push_back(&head, *env);

        mx_sort_list(head, mx_sort_predicate);

        while (head)
        {
            printf("%s\n", (char *)(head->data));
            head = head->next;
        }
    }
    else if (command->argc >= 2)
    {
        for (int i = 1; i < command->argc - 1; i++)
        {
            char **splitted_arg = mx_str_split(command->argv[i], '=');

            if (splitted_arg != NULL)
            {
                setenv(splitted_arg[0], splitted_arg[1], 1);
            }

            free(splitted_arg);
        }
    }

    return 1;
}

int mx_unset_builtin(t_process *command)
{
    /*  if (command->argc >= 1)
    {
        for (int i = 0; i < command->argc; i++)
            unsetenv(command->args[i]);
    } */

    return 1;
}

int mx_env_builtin(t_process *command)
{
    if (command->argc == 1)
    {
        for (char **env = environ; *env; ++env)
            printf("%s\n", *env);
    }
    else if (command->argc == 2)
    {
        if (mx_env_valid_format(command->argv[1]))
        {
            for (char **env = environ; *env; ++env)
                printf("%s\n", *env);

            printf("%s\n", command->argv[1]);
        }
        else
        {
            t_job *job = ush_parse_command(mx_str_arr_to_str((const char **)(&command->argv[1]), command->argc - 1));
            int status = ush_launch_job(job);
        }
    }
}

// #endif
int mx_pwd_builtin(t_process *command)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);

    return 0;
}

int mx_which_builtin(t_process *command)
{
    if (command->argc > 1)
    {
        t_list *output = NULL;
        char *path = getenv("PATH");
        char **arr = NULL;

        if (!path)
            path = "";

        arr = mx_strsplit(path, ":");

        int i = 0;
        char *name = NULL;
        DIR *dptr;
        struct dirent *ds;

        while (arr[i] != NULL)
        {
            dptr = opendir(arr[i]);
            if (dptr != NULL)
            {
                while ((ds = readdir(dptr)) != 0)
                {
                    if (strcmp(ds->d_name, command->argv[1]) == 0 && command->argv[1][0] != '.')
                    {
                        name = strcat(arr[i], "/");
                        name = strcat(name, command->argv[1]);
                        mx_push_back(&output, name);
                    }
                }
                closedir(dptr);
            }
            i++;
        }
        if (!mx_is_arguments_contains_flag((const char **)(&(command->argv[1])), command->argc - 1, 's'))
            mx_which_print_res(output, mx_is_arguments_contains_flag((const char **)(&(command->argv[1])), command->argc - 1, 'a'));
    }

    return 0;
}

int mx_fg_builtin(t_process *proccess)
{
    if (proccess->argc < 2)
    {
        printf("usage: fg <pid>\n");
        return -1;
    }

    int status;
    pid_t pid;
    int job_id = -1;

    if (proccess->argv[1][0] == '%')
    {
        job_id = atoi(proccess->argv[1] + 1);
        pid = get_pgid_by_job_id(job_id);
        if (pid < 0)
        {
            printf("ush: fg %s: no such job\n", proccess->argv[1]);
            return -1;
        }
    }
    else
    {
        pid = atoi(proccess->argv[1]);
    }

    if (kill(-pid, SIGCONT) < 0)
    {
        printf("ush: fg %d: job not found\n", pid);
        return -1;
    }

    tcsetpgrp(0, pid);

    if (job_id > 0)
    {
        set_job_status(job_id, STATUS_CONTINUED);
        print_job_status(job_id);
        if (wait_for_job(job_id) >= 0)
        {
            remove_job(job_id);
        }
    }
    else
    {
        wait_for_pid(pid);
    }

    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpid());
    signal(SIGTTOU, SIG_DFL);

    return 0;
}

void mx_which_print_res(t_list *head, bool a_flag)
{
    while (head)
    {
        printf("%s\n", (char *)(head->data));

        if (!a_flag)
            break;

        head = head->next;
    }
}

int mx_echo_builtin(t_process *command)
{
    int not_flag_pos = 0;

    int i = 0;
    int argc = command->argc - 1;
    char **args;

    if (argc)
        args = &(command->argv[1]);

    if (argc)
        while (mx_is_flag(args[i]) && i < argc)
            i++;

    if (i < argc)
    {
        for (int j = i; j < argc - 1; j++)
            printf("%s ", args[j]);

        printf("%s", args[argc - 1]);
    }

    if (!mx_is_arguments_contains_flag((const char **)args, argc, 'n'))
        printf("\n");

    return 0;
}

int mx_cd_builtin(t_process *command)
{
    if (command->argc == 1)
    {
        setenv("OLDPWD", shell->pw_dir, 1);
        chdir(shell->pw_dir);
        setenv("PWD", shell->pw_dir, 1);
        ush_update_cwd_info();
        return 0;
    }

    if (chdir(command->argv[1]) == 0)
    {
        ush_update_cwd_info();
        return 0;
    }
    else
    {
        printf("ush: cd %s: No such file or directory\n", command->argv[1]);
        return 0;
    }

    /* char *dir_name;

    if (command->args == NULL || command->args[0] == NULL)
    {
        dir_name = getenv("HOME");
        printf("%s", dir_name);
    }
    else
        dir_name = command->args[0];

    if (chdir((const char *)dir_name) != 0)
        perror("lsh"); */

    return 0;
}
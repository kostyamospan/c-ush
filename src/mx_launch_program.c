#include "../inc/ush.h"

int mx_launch_program(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        have_child_proccess = true;

        if (execvp(args[0], args) == -1)
            perror("ush");

        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("ush");
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        have_child_proccess = false;
    }

    return 1;
}
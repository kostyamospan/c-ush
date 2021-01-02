#include "../inc/ush.h"

void ush_init()
{
    struct sigaction sigint_action = {
        .sa_handler = &sigint_handler,
        .sa_flags = 0};

    sigemptyset(&sigint_action.sa_mask);
    sigaction(SIGINT, &sigint_action, NULL);

    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    pid_t pid = getpid();
    setpgid(pid, pid);
    tcsetpgrp(0, pid);

    shell = (t_shell_info *)malloc(sizeof(t_shell_info));
    // getlogin_r(shell->cur_user, sizeof(shell->cur_user));

    struct passwd *pw = getpwuid(getuid());
    strcpy(shell->pw_dir, pw->pw_dir);
    // strcpy(shell->cur_user, pw->pw_name);

    int i;
    for (i = 0; i < NR_JOBS; i++)
    {
        shell->jobs[i] = NULL;
    }

    ush_update_cwd_info();
}

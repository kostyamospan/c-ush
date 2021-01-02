#include "../inc/ush.h"

int ush_launch_process(t_job *job, t_process *proc, int in_fd, int out_fd, int mode)
{
    proc->status = STATUS_RUNNING;
    
    if (proc->type != COMMAND_EXTERNAL && ush_execute_builtin_command(proc))
    {
        return 0;
    }

    pid_t childpid;
    int status = 0;

    childpid = fork();

    if (childpid < 0)
    {
        return -1;
    }
    else if (childpid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        proc->pid = getpid();
        if (job->pgid > 0)
        {
            setpgid(0, job->pgid);
        }
        else
        {
            job->pgid = proc->pid;
            setpgid(0, job->pgid);
        }

        if (in_fd != 0)
        {
            dup2(in_fd, 0);
            close(in_fd);
        }

        if (out_fd != 1)
        {
            dup2(out_fd, 1);
            close(out_fd);
        }

        if (execvp(proc->argv[0], proc->argv) < 0)
        {
            printf("ush: %s: command not found\n", proc->argv[0]);
            exit(0);
        }

        exit(0);
    }
    else
    {
        proc->pid = childpid;
        if (job->pgid > 0)
        {
            setpgid(childpid, job->pgid);
        }
        else
        {
            job->pgid = proc->pid;
            setpgid(childpid, job->pgid);
        }

        if (mode == FOREGROUND_EXECUTION)
        {
            tcsetpgrp(0, job->pgid);
            status = wait_for_job(job->id);
            signal(SIGTTOU, SIG_IGN);
            tcsetpgrp(0, getpid());
            signal(SIGTTOU, SIG_DFL);
        }
    }

    return status;
}

int ush_launch_job(t_job *job)
{
    t_process *proc;
    int status = 0, in_fd = 0, fd[2], job_id = -1;

    check_zombie();

    if (job->root->type == COMMAND_EXTERNAL)
    {
        job_id = insert_job(job);
    }

    for (proc = job->root; proc != NULL; proc = proc->next)
    {
        if (proc == job->root && proc->input_path != NULL)
        {
            in_fd = open(proc->input_path, O_RDONLY);
            if (in_fd < 0)
            {
                printf("ush: no such file or directory: %s\n", proc->input_path);
                remove_job(job_id);
                return -1;
            }
        }
        if (proc->next != NULL)
        {
            pipe(fd);
            status = ush_launch_process(job, proc, in_fd, fd[1], PIPELINE_EXECUTION);
            close(fd[1]);
            in_fd = fd[0];
        }
        else
        {
            int out_fd = 1;
            if (proc->output_path != NULL)
            {
                out_fd = open(proc->output_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                if (out_fd < 0)
                {
                    out_fd = 1;
                }
            }
            status = ush_launch_process(job, proc, in_fd, out_fd, job->mode);
        }
    }

    if (job->root->type == COMMAND_EXTERNAL)
    {
        if (status >= 0 && job->mode == FOREGROUND_EXECUTION)
        {
            remove_job(job_id);
        }
        else if (job->mode == BACKGROUND_EXECUTION)
        {
            print_processes_of_job(job_id);
        }
    }

    return status;
}

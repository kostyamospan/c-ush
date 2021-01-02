#include "../inc/ush.h"

int get_job_id_by_pid(int pid)
{
    int i;
    t_process *proc;

    for (i = 1; i <= NR_JOBS; i++)
    {
        if (shell->jobs[i] != NULL)
        {
            for (proc = shell->jobs[i]->root; proc != NULL; proc = proc->next)
            {
                if (proc->pid == pid)
                {
                    return i;
                }
            }
        }
    }

    return -1;
}

t_job *get_job_by_id(int id)
{
    if (id > NR_JOBS)
    {
        return NULL;
    }

    return shell->jobs[id];
}

int get_pgid_by_job_id(int id)
{
    t_job *job = get_job_by_id(id);

    if (job == NULL)
    {
        return -1;
    }

    return job->pgid;
}

int get_proc_count(int id, int filter)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    int count = 0;
    t_process *proc;
    for (proc = shell->jobs[id]->root; proc != NULL; proc = proc->next)
    {
        if (filter == PROC_FILTER_ALL ||
            (filter == PROC_FILTER_DONE && proc->status == STATUS_DONE) ||
            (filter == PROC_FILTER_REMAINING && proc->status != STATUS_DONE))
        {
            count++;
        }
    }

    return count;
}

int get_next_job_id()
{
    int i;

    for (i = 1; i <= NR_JOBS; i++)
    {
        if (shell->jobs[i] == NULL)
        {
            return i;
        }
    }

    return -1;
}

int print_processes_of_job(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    printf("[%d]", id);

    t_process *proc;
    for (proc = shell->jobs[id]->root; proc != NULL; proc = proc->next)
    {
        printf(" %d", proc->pid);
    }
    printf("\n");

    return 0;
}

int print_job_status(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    printf("[%d]", id);

    t_process *proc;
    for (proc = shell->jobs[id]->root; proc != NULL; proc = proc->next)
    {
        printf("\t%d\t%s\t%s", proc->pid,
               STATUS_STRING[proc->status], proc->command);
        if (proc->next != NULL)
        {
            printf("|\n");
        }
        else
        {
            printf("\n");
        }
    }

    return 0;
}

int release_job(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    t_job *job = shell->jobs[id];
    t_process *proc, *tmp;
    for (proc = job->root; proc != NULL;)
    {
        tmp = proc->next;
        free(proc->command);
        free(proc->argv);
        free(proc->input_path);
        free(proc->output_path);
        free(proc);
        proc = tmp;
    }

    free(job->command);
    free(job);

    return 0;
}

int insert_job(t_job *job)
{
    int id = get_next_job_id();

    if (id < 0)
    {
        return -1;
    }

    job->id = id;
    shell->jobs[id] = job;
    return id;
}

int remove_job(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    release_job(id);
    shell->jobs[id] = NULL;

    return 0;
}

int is_job_completed(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return 0;
    }

    t_process *proc;
    for (proc = shell->jobs[id]->root; proc != NULL; proc = proc->next)
    {
        if (proc->status != STATUS_DONE)
        {
            return 0;
        }
    }

    return 1;
}

int set_process_status(int pid, int status)
{
    int i;
    t_process *proc;

    for (i = 1; i <= NR_JOBS; i++)
    {
        if (shell->jobs[i] == NULL)
        {
            continue;
        }
        for (proc = shell->jobs[i]->root; proc != NULL; proc = proc->next)
        {
            if (proc->pid == pid)
            {
                proc->status = status;
                return 0;
            }
        }
    }

    return -1;
}

int set_job_status(int id, int status)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    int i;
    t_process *proc;

    for (proc = shell->jobs[id]->root; proc != NULL; proc = proc->next)
    {
        if (proc->status != STATUS_DONE)
        {
            proc->status = status;
        }
    }

    return 0;
}

int wait_for_pid(int pid)
{
    int status = 0;

    waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status))
    {
        set_process_status(pid, STATUS_DONE);
    }
    else if (WIFSIGNALED(status))
    {
        set_process_status(pid, STATUS_TERMINATED);
    }
    else if (WSTOPSIG(status))
    {
        status = -1;
        set_process_status(pid, STATUS_SUSPENDED);
    }

    return status;
}

int wait_for_job(int id)
{
    if (id > NR_JOBS || shell->jobs[id] == NULL)
    {
        return -1;
    }

    int proc_count = get_proc_count(id, PROC_FILTER_REMAINING);
    int wait_pid = -1, wait_count = 0;
    int status = 0;

    do
    {
        wait_pid = waitpid(-shell->jobs[id]->pgid, &status, WUNTRACED);
        wait_count++;

        if (WIFEXITED(status))
        {
            set_process_status(wait_pid, STATUS_DONE);
        }
        else if (WIFSIGNALED(status))
        {
            set_process_status(wait_pid, STATUS_TERMINATED);
        }
        else if (WSTOPSIG(status))
        {
            status = -1;
            set_process_status(wait_pid, STATUS_SUSPENDED);
            if (wait_count == proc_count)
            {
                print_job_status(id);
            }
        }
    } while (wait_count < proc_count);

    return status;
}

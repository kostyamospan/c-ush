#include "../inc/ush.h"

void check_zombie()
{
    int status, pid;
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
    {
        if (WIFEXITED(status))
        {
            set_process_status(pid, STATUS_DONE);
        }
        else if (WIFSTOPPED(status))
        {
            set_process_status(pid, STATUS_SUSPENDED);
        }
        else if (WIFCONTINUED(status))
        {
            set_process_status(pid, STATUS_CONTINUED);
        }

        int job_id = get_job_id_by_pid(pid);
        if (job_id > 0 && is_job_completed(job_id))
        {
            print_job_status(job_id);
            remove_job(job_id);
        }
    }
}
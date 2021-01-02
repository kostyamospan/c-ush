#include "../inc/ush.h"

void ush_loop()
{
    char *line;

    t_job *job;
    int status = 1;

    while (1)
    {
        ush_print_promt();
        line = ush_read_line();

        if (strlen(line) == 0)
        {
            check_zombie();
            continue;
        }

        mx_replace_char(line, '\n', ';');
        t_2d_arr *commands_unparsed = mx_split_commands(line);

        for (int i = 0; i < commands_unparsed->size; i++)
        {
            job = ush_parse_command(commands_unparsed->data[i]);
            status = ush_launch_job(job);
        }

        // free(commands_unparsed);
    }
}

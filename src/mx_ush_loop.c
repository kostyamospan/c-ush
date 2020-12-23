#include "../inc/ush.h"

void mx_ush_loop(char **args)
{
    int execution_status;
    do
    {
        signal(SIGINT, mx_ctrl_c_handler);
        have_child_proccess = false;

        execution_status = 1;

        printf("u&h> ");
        char *str = mx_getline();
        mx_replace_char(str, '\n', ';');

        t_2d_arr *commands_unparsed = mx_split_commands(str);

        for (int i = 0; i < commands_unparsed->size; i++)
            execution_status = mx_process_command(((char **)(commands_unparsed->data))[i]);

        free(str);
    } while (execution_status);
}

#include "../inc/ush.h"

void mx_ctrl_c_handler(int id)
{
    if (have_child_proccess)
    {
        have_child_proccess = false;
        exit(1);
    }
}

void sigint_handler(int signal)
{
    printf("\n");
}

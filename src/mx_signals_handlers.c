#include "../inc/ush.h"

void mx_ctrl_c_handler(int id)
{
    printf("exit\n");

    if (have_child_proccess)
    {
        have_child_proccess = false;
        exit(1);
    }
}

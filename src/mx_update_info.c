#include "../inc/ush.h"

void ush_update_cwd_info()
{
    getcwd(shell->cur_dir, sizeof(shell->cur_dir));
}

#include "../inc/ush.h"

bool mx_env_valid_format(const char *env)
{
    return mx_str_indexof(env, '=') != -1 ? true : false;
}

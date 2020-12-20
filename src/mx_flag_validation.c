#include "../inc/ush.h"

bool mx_is_flag(const char *str)
{
    if (mx_strlen(str) >= 2 && str[0] == '-')
        return true;

    return false;
}

bool mx_is_arguments_contains_flag(const char **args, int argc, const char flag)
{
    for (int i = 0; i < argc; i++)
        if (mx_is_flag(args[i]) && mx_str_indexof(args[i], flag) > -1)
            return true;

    return false;
}
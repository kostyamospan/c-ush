#include "../inc/libmx.h"

bool mx_is_str_contain(const char *str, const char ch)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == (char)ch)
            return true;

        i++;
    }
    return false;
}

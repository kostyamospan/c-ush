#include "../inc/ush.h"

void mx_replace_char(char *str, const char which, const char whith)
{
    for (int i = 0; i < mx_strlen(str); i++)
    {
        if (str[i] == which)
            str[i] = whith;
    }
}

#include "../inc/libmx.h"

long mx_atoi_positive(char *str)
{
    long num = 0;
    long i = 0, sign = 1;

    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
        i++;

    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }

    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {

        num = num * 10 + (str[i] - '0');
        i++;
    }

    if ((!mx_isdigit(str[i]) && !mx_isspace(str[i]) && str[i]) || sign < 0)
    {
        return -1;
    }

    return sign * num;
}

#include "../inc/libmx.h"

void mx_printint(int num)
{
    if (num == 0)
    {
        mx_printchar('0');
        return;
    }

    if (num < 0)
    {
        mx_printchar('-');
        num *=-1;
    }
    int num_copy = num;
    int count = 0;

    while (num_copy != 0)
    {
        num_copy /= 10;
        ++count;
    }
    char str[count];
    int i = 0;

    while (num > 0)
    {
        str[i] = (num % 10) + '0';
        i++;
        num /= 10;
    }

    for (int j = count - 1; j >= 0; j--)
        mx_printchar(str[j]);
}

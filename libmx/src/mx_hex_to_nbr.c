#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long base = 1;
    int len = 0;

    while (hex[len])
        len++;

    unsigned long dec_val = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        if (mx_isdigit(hex[i]))
        {
            dec_val += (hex[i] - 48) * base;
            base = base * 16;
        }
        else if (mx_isalpha(hex[i]))
        {
            if (hex[i] >= 'A' && hex[i] <= 'F')
            {
                dec_val += (hex[i] - 55) * base;
                base = base * 16;
            }
            else if (hex[i] >= 'a' && hex[i] <= 'f')
            {
                dec_val += (hex[i] - 87) * base;
                base = base * 16;
            }
            else return 0;
        }
        else return 0;
    }
    return dec_val;
}

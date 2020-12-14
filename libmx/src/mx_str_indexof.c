int mx_str_indexof(const char *str, const char symb)
{
    int i = 0;

    while (str[i])
    {
        if (str[i] == symb)
            return i;
        i++;
    }

    return -1;
}

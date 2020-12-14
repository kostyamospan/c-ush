int mx_str_contains(const char *str, const char symb)
{
    int f = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == symb)
            f++;
        i++;
    }

    return f == 0 ? -1 : f;
}

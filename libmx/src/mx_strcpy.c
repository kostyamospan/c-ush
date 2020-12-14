char *mx_strcpy(char *dst, const char *src)
{
    char *temp = dst;
    while ((*dst++ = *src++))
        ;
    return temp;
}

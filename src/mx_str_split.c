#include "../inc/ush.h"

char **mx_str_split(char *a_str, const char a_delim)
{
    int count = 0;
    char *token = strtok(mx_strdup(a_str), (char *)(&a_delim));

    while (token != NULL)
    {
        count++;
        token = strtok(NULL, (char *)(&a_delim));
    }
    free(token);

    char **arr = malloc((count + 1) * sizeof(char *));
    token = strtok(a_str, (char *)(&a_delim));
    int i = 0;

    while (token != NULL)
    {
        arr[i++] = mx_strdup(token);
        token = strtok(NULL, (char *)(&a_delim));
    }
    arr[count] = NULL;

    return arr;
}

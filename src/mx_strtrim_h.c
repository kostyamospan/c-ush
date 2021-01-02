#include "../inc/ush.h"

char *helper_strtrim(char *line)
{
    char *head = line, *tail = line + strlen(line);

    while (*head == ' ')
    {
        head++;
    }
    while (*tail == ' ')
    {
        tail--;
    }
    *(tail + 1) = '\0';

    return head;
}

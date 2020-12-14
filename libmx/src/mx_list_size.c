#include "../inc/libmx.h"

int mx_list_size(t_list *list)
{
    t_list *current = list;
    int length = 0;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    return length;
}

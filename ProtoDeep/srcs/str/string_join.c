#include "pd_main.h"

char    *str_join(char *head, char *tail)
{
    if (!head || str_len(head) == 0)
        return (tail);
    else if (!tail || str_len(tail) == 0)
        return (head);
    return (NULL);
}
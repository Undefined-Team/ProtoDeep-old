#include "pd_main.h"

char    *string_join(char *head, char *tail)
{
    if (!head || string_len(head) == 0)
        return (tail);
    else if (!tail || string_len(tail) == 0)
        return (head);
    
}
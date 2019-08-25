#include "pd_main.h"

char    *str_join(char *head, char *tail)
{
    char    *joined;
    size_t  head_len;
    size_t  tail_len;
    size_t  i;
    size_t  j;

    if (!head || (head_len = str_len(head)) == 0)
        return (str_dup(tail));
    else if (!tail || (tail_len = str_len(tail)) == 0)
        return (str_dup(head));
    joined = (char *)malloc(head_len + tail_len + 1);
    i = -1;
    while (++i < head_len)
        joined[i] = head[i];
    j = -1;
    while (++j < tail_len)
        joined[i + j] = tail[j];
    return (joined);
}
#include "pd_main.h"

t_carr  str_join(t_carr head, t_carr tail)
{
    t_carr  joined;
    size_t  i;
    size_t  j;

    if (!head.arr || head.len == 0)
        return (str_dup(tail, tail.len));
    else if (!tail.arr || tail.len == 0)
        return (str_dup(head, head.len));
    joined.arr = (char *)malloc(head.len + tail.len + 1);
    i = -1;
    while (++i < head.len && head.arr[i])
        joined.arr[i] = head.arr[i];
    j = -1;
    while (++j < tail.len && tail.arr[j])
        joined.arr[i + j] = tail.arr[j];
    joined.len = str_len(joined);
    return (joined);
}
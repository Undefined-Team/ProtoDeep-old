#include "pd_main.h"

t_arr  str_join(t_arr head, t_arr tail)
{
    t_arr  joined;
    size_t  i;
    size_t  j;

    if (!head.val || head.len == 0)
        return (str_dup(tail, tail.len));
    else if (!tail.val || tail.len == 0)
        return (str_dup(head, head.len));
    joined = arrInit(T_CHAR, head.len + tail.len + 1);
    i = -1;
    while (++i < head.len && ((char *)head.val)[i])
        ((char *)joined.val)[i] = ((char *)head.val)[i];
    j = -1;
    while (++j < tail.len && ((char *)tail.val)[j])
        ((char *)joined.val)[i + j] = ((char *)tail.val)[j];
    ((char *)joined.val)[i + j] = '\0';
    joined.len = str_len(joined);
    return (joined);
}
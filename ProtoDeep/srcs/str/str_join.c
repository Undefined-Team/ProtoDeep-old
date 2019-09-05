#include "pd_main.h"

pd_arr  pd_str_join(pd_arr head, pd_arr tail)
{
    pd_arr  joined;
    size_t  i;
    size_t  j;

    if (!head.val || head.len == 0)
        return (pd_str_dup(tail, tail.len));
    else if (!tail.val || tail.len == 0)
        return (pd_str_dup(head, head.len));
    joined = pd_arr_init(PD_T_CHAR, head.len + tail.len);
    i = -1;
    while (++i < head.len && ((char *)head.val)[i])
        ((char *)joined.val)[i] = ((char *)head.val)[i];
    j = -1;
    while (++j < tail.len && ((char *)tail.val)[j])
        ((char *)joined.val)[i + j] = ((char *)tail.val)[j];
    ((char *)joined.val)[i + j] = '\0';
    joined.len = pd_str_len(joined);
    return (joined);
}
#include "pd_main.h"

pd_arr  *pd_str_join(pd_arr *head, pd_arr *tail)
{
    pd_arr  *joined;
    size_t  i;
    size_t  j;

    char *a_head = (char *)head->val;
    char *a_tail = (char *)tail->val;
    size_t head_len = head->len;
    size_t tail_len = tail->len;
    if (!a_head || head_len == 0)
        return (pd_str_dup(tail, tail_len));
    else if (!a_tail || tail_len == 0)
        return (pd_str_dup(head, head_len));
    joined = pd_arr_init(PD_T_CHAR, head_len + tail_len);
    char *a_joined = (char*)joined->val;
    i = -1;
    while (++i < head_len && a_head[i])
        a_joined[i] = a_head[i];
    j = -1;
    while (++j < tail_len && a_tail[j])
        a_joined[i + j] = a_tail[j];
    a_joined[i + j] = '\0';
    joined->len = pd_str_len(joined);
    return (joined);
}
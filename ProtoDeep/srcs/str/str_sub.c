#include "pd_main.h"

pd_arr  pd_str_sub(pd_arr str, size_t start, size_t length)
{
    pd_arr  sub;
    size_t i;

    sub = pd_arr_init(PD_T_CHAR, str.len - start);
    for (i = start; i < start + length && ((char *)str.val)[i]; i++)
        ((char *)sub.val)[i - start] = ((char *)str.val)[i];
    ((char *)sub.val)[i - start] = 0;
    sub.len = pd_str_len(sub);
    return (sub);
}
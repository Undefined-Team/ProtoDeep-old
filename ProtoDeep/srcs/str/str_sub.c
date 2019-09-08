#include "pd_main.h"

pd_arr  pd_str_sub(pd_arr str, size_t start, size_t length)
{
    pd_arr  sub;
    size_t i;

    char *a_str = (char*)str.val;
    sub = pd_arr_init(PD_T_CHAR, str.len - start);
    char *a_sub = (char*)sub.val;
    for (i = start; i < start + length && a_str[i]; i++)
        a_sub[i - start] = a_str[i];
    a_sub[i - start] = 0;
    sub.len = pd_str_len(sub);
    return (sub);
}
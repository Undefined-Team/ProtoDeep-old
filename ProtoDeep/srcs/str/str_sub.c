#include "pd_main.h"

t_arr  str_sub(t_arr str, size_t start, size_t length)
{
    t_arr  sub;
    size_t i;

    if (start > str.len)
        return (str);
    sub = arrInit(T_CHAR, str.len - start);
    for (i = start; i < start + length && ((char *)str.val)[i]; i++)
        ((char *)sub.val)[i - start] = ((char *)str.val)[i];
    ((char *)sub.val)[i] = 0;
    if (length > str.len)
        return (sub);
    ((char *)sub.val)[length] = 0;
    sub.len = str_len(sub);
    return (sub);
}
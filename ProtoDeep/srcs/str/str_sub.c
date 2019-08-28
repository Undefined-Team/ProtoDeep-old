#include "pd_main.h"

t_arr  str_sub(t_arr str, size_t start, size_t length)
{
    t_arr  sub;
    size_t i;

    // printf("%s, %zd, %zd, %zd\n", ((char *)str.val), start, length, str.len);
    if (start > str.len)
        return (str);
    sub = arrInit(T_CHAR, str.len - start - 1);
    for (i = start; i < start + length && ((char *)str.val)[i]; i++)
        ((char *)sub.val)[i - start] = ((char *)str.val)[i];
    ((char *)sub.val)[i] = 0;
    // printf("%s\n", ((char *)sub.val));
    if (length > str.len)
        return (sub);
    ((char *)sub.val)[length] = 0;
    sub.len = str_len(sub);
    return (sub);
}
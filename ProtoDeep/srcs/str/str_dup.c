#include "pd_main.h"

t_carr  str_dup(t_carr str, size_t len)
{
    t_carr  dup;
    size_t  i;

    if (!str.arr)
        return (str);
    dup.arr = (char *)malloc(len + 1);
    i = -1;
    while (++i < len)
        dup.arr[i] = str.arr[i];
    dup.arr[i] = 0;
    dup.len = len;
    return (dup);
}
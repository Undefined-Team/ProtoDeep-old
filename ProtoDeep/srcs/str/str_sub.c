#include "pd_main.h"

t_carr  str_sub(t_carr str, size_t start, size_t length)
{
    t_carr  sub;

    if (start > str.len)
        return (str);
    sub = dast_new_carr(&str.arr[start], str.len - start - 1);
    if (length > str.len)
        return (sub);
    sub.arr[length] = 0;
    sub.len = length;
    return (sub);
}
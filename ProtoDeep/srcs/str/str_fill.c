#include "pd_main.h"

t_carr  str_fill(char c, size_t len)
{
    t_carr  str;

    str.len = len;
    str.arr = (char *)malloc(len + 1);
    for (size_t i = 0; i <= len; i++)
    {
        str.arr[i] = c;
    }
    return (str);
}
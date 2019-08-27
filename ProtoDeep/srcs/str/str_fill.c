#include "pd_main.h"

t_arr  str_fill(char c, size_t len)
{
    t_arr  str;

    str = arrInit(T_CHAR, c == 0 ? 0 : len);
    for (size_t i = 0; i <= len; i++)
        ((char *)str.val)[i] = c;
    return (str);
}
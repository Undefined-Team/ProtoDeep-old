#include "pd_main.h"

t_arr  str_fill(char c, size_t len)
{
    t_arr  str;
    size_t  i;

    str = arrInit(T_CHAR, len);
    for (i = 0; i < len; i++)
        ((char *)str.val)[i] = c;
    ((char *)str.val)[i] = '\0';
    return (str);
}
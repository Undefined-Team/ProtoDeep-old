#include "pd_main.h"

pd_arr  str_fill(char c, size_t len)
{
    pd_arr  str;
    size_t  i;

    str = pd_arr_init(PD_T_CHAR, len);
    for (i = 0; i < len; i++)
        ((char *)str.val)[i] = c;
    ((char *)str.val)[i] = '\0';
    return (str);
}
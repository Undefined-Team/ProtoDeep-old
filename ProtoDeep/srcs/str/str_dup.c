#include "pd_main.h"

t_arr  str_dup(t_arr str, size_t len)
{
    t_arr  dup;
    size_t i;

    if (!str.val)
        return (str);
    dup = arrInit(T_CHAR, len);
    for (i = 0; i < len; i++)
        ((char *)dup.val)[i] = ((char *)str.val)[i];
    ((char *)dup.val)[i] = 0;
    return (dup);
}
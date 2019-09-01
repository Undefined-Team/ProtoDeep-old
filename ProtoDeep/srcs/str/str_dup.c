#include "pd_main.h"

pd_arr  pd_str_dup(pd_arr str, size_t len)
{
    pd_arr  dup;
    size_t i;

    if (!str.val)
        return (str);
    dup = arrInit(PD_T_CHAR, len);
    for (i = 0; i < len && ((char *)str.val)[i]; i++)
        ((char *)dup.val)[i] = ((char *)str.val)[i];
    ((char *)dup.val)[i] = 0;
    return (dup);
}
#include "pd_main.h"

pd_arr  *pd_str_dup(pd_arr *str, size_t len)
{
    pd_arr  *dup;
    size_t i;

    if (!str->val)
        return (str);
    dup = pd_arr_init(PD_T_CHAR, len);
    char *a_str = (char*)str->val;
    char *a_dup = (char*)dup->val;
    for (i = 0; i < len && a_str[i]; i++)
        a_dup[i] = a_str[i];
    a_dup[i] = 0;
    return (dup);
}
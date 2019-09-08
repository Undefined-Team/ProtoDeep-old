#include "pd_main.h"

pd_arr  *str_fill(char c, size_t len)
{
    pd_arr  *str;
    size_t  i;

    str = pd_arr_init(PD_T_CHAR, len);
    char *a_str = (char*)str->val;
    for (i = 0; i < len; i++)
        a_str[i] = c;
    a_str[i] = '\0';
    return (str);
}
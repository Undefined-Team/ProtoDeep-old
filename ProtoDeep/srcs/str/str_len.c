#include "pd_main.h"

size_t  pd_str_len(pd_arr str)
{
    size_t  i = 0;

    char *a_str = (char*)str.val;
    if (!a_str)
        return 0;
    while (a_str[i])
        i++;
    return (i);
}
#include "pd_main.h"

size_t  pd_str_len(pd_arr str)
{
    size_t  i = 0;

    if (!str.val)
        return 0;
    while (((char *)str.val)[i])
        i++;
    return (i);
}
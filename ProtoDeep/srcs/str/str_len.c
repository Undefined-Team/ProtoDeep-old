#include "pd_main.h"

size_t  str_len(t_carr str)
{
    size_t  i = 0;

    while (str.arr && str.arr[i])
        i++;
    return (i);
}
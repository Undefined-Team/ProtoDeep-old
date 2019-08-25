#include "pd_main.h"

size_t  str_len(char *str)
{
    size_t  i = 0;

    while (str && str[i])
        i++;
    return (i);
}
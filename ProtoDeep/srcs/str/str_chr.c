#include "pd_main.h"

int     str_chr(t_arr str, char c)
{
    size_t  i;

    i = 0;
    while (((char *)str.val)[i])
    {
        if (((char *)str.val)[i] == c)
            return (1);
        i++;
    }
    return (0);
}
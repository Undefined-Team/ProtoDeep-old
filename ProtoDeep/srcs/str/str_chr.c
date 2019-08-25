#include "pd_main.h"

int     str_chr(t_carr str, char c)
{
    size_t  i;

    i = 0;
    while (str.arr[i])
    {
        if (str.arr[i] == c)
            return (1);
        i++;
    }
    return (0);
}
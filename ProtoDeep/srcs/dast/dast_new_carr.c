#include "pd_main.h"

t_carr  dast_new_carr(char *str, size_t len)
{
    t_carr new_array;

    new_array.len = len;
    if (!str)
    {
        new_array.len = -1;
        new_array.arr = NULL;
    }
    new_array.arr = (char *)malloc(len + 1);
    for (size_t i = 0; i < len; i++)
        new_array.arr[i] = str[i];
    new_array.arr[len] = 0;
    return new_array;
}
#include "pd_main.h"

t_carr  dast_new_carr(char *str, size_t len)
{
    t_carr new_array;

    new_array.len = len;
    new_array.arr = str;
    return new_array;
}
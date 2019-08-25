#include "pd_main.h"

t_farr  dast_new_farr(size_t len)
{
    t_farr new_array;

    new_array.len = len;
    if(!(new_array.arr = malloc(sizeof(float) * len)))
        new_array.len = 0;
    return new_array;
}
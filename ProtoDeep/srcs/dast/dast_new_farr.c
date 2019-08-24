#include "pd_main.h"

t_farr  dast_new_farr(size_t len)
{
    t_farr new_array;

    new_array.len = len;
    new_array.arr = malloc(sizeof(float) * len);
    return new_array;
}
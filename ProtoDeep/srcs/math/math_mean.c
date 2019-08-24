#include "pd_main.h"

float math_mean(t_farr x)
{
    float sum = 0;

    for (size_t i = 0; i < x.len; i++)
    {
        sum += x.arr[i];
    }
    return sum / x.len;
}
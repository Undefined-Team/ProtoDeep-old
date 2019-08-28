#include "pd_main.h"

float math_mean(t_float_a x)
{
    float sum = 0;

    if (x.type != T_FLOAT)
        return 0;
    for (size_t i = 0; i < x.len; i++)
        sum += ((float*)x.val)[i];
    return sum / x.len;
}
#include "pd_main.h"

float pd_math_mean(t_float_a x)
{
    float sum = 0;

    if (x.type != PD_T_FLOAT)
        return 0;
    for (size_t i = 0; i < x.len; i++)
        sum += ((float*)x.val)[i];
    return sum / x.len;
}
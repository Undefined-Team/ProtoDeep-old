#include "pd_main.h"

float pd_math_stdev(pd_float_a x, float mean)
{
    float sum = 0;

    if (x.type != PD_T_FLOAT)
        return 0;
    for (size_t i = 0; i < x.len; i++)
        sum += pd_math_pow(((float*)x.val)[i] - mean, 2);
    return pd_math_sqrt(sum / x.len);
}
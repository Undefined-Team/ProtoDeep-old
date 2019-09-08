#include "pd_main.h"

float pd_math_stdev(pd_float_a x, float mean)
{
    float sum = 0;

    if (x.type != PD_T_FLOAT)
        return 0;
    size_t x_len = x.len;
    float *a_x = (float*)x.val;
    for (size_t i = 0; i < x_len; i++)
        sum += pd_math_pow(a_x[i] - mean, 2);
    return pd_math_sqrt(sum / x_len);
}
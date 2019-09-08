#include "pd_main.h"

float pd_math_mean(pd_float_a x)
{
    float sum = 0;

    if (x.type != PD_T_FLOAT)
        return 0;
    size_t x_len = x.len;
    float* a_x = (float*)x.val;
    for (size_t i = 0; i < x_len; i++)
        sum += a_x[i];
    return sum / x_len;
}
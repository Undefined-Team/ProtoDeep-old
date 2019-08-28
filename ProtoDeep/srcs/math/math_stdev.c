#include "pd_main.h"

float math_stdev(t_float_a x, float mean)
{
    float sum = 0;

    if (x.type != T_FLOAT)
        return 0;
    for (size_t i = 0; i < x.len; i++)
        sum += math_pow(((float*)x.val)[i] - mean, 2);
    return math_sqrt(sum / x.len);
}
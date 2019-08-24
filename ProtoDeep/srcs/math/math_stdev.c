#include "pd_main.h"

float math_stdev(t_farr x, float mean)
{
    float sum = 0;

    for (size_t i = 0; i < x.len; i++)
    {
        sum += math_pow(x.arr[i] - mean, 2);
    }
    return math_sqrt(sum / x.len);
}
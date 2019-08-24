#include "pd_main.h"

float math_stdev(float *x, size_t len, float mean)
{
    float sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += math_pow(x[i] - mean, 2);
    }
    return math_sqrt(sum / len);
}
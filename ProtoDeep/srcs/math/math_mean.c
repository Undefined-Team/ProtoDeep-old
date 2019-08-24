#include "pd_main.h"

float math_mean(float *x, size_t len)
{
    float sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += x[i];
    }
    return sum / len;
}
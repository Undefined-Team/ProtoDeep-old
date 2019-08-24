#include "pd_main.h"

float   *prep_stdiz(float *x, size_t len)
{
    float *y;
    float mean;
    float std_dev;

    y = prep_minmax_scal(x, len);
    mean = math_mean(y, len);
    std_dev = math_stdev(y, len, mean);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (y[i] - mean) / std_dev;
    }
    return y;
}
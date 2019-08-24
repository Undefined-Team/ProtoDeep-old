#include "pd_main.h"

float   *prep_minmax_scal(float *x, size_t len)
{
    float *y;
    float xmax;
    float xmin;

    xmax = math_max_a(x, len);
    xmin = math_min_a(x, len);
    y = malloc(sizeof(float) * len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (x[i] - xmin) / (xmax - xmin);
    }
    return y;
}
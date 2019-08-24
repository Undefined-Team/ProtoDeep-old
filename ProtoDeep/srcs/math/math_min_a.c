#include "pd_math.h"

float   math_min_a(float *x, size_t len)
{
    float min;
    bool ftime = false;

    for (size_t i = 0; i < len; i++)
    {
        if (!ftime || min > x[i])
        {
            ftime = true;
            min = x[i];
        }
    }
    return ftime ? min : 0;
}
#include "pd_main.h"

float   math_max_a(float *x, size_t len)
{
    float max;
    bool ftime = false;

    for (size_t i = 0; i < len; i++)
    {
        if (!ftime || max < x[i])
        {
            ftime = true;
            max = x[i];
        }
    }
    return ftime ? max : 0;
}
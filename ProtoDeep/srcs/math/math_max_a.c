#include "pd_main.h"

float   pd_math_max_a(pd_float_a x)
{
    float min;
    bool ftime = false;

    if (x.type != PD_T_FLOAT)
        return (0);
    size_t x_len = x.len;
    float *a_x = (float*)x.val;
    for (size_t i = 0; i < x_len; i++)
    {
        if (!ftime || min < a_x[i])
        {
            ftime = true;
            min = a_x[i];
        }
    }
    return ftime ? min : 0;
}
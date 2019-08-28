#include "pd_main.h"

float   math_min_a(t_float_a x)
{
    float min;
    bool ftime = false;

    if (x.type != T_FLOAT)
        return (0);
    for (size_t i = 0; i < x.len; i++)
    {
        if (!ftime || min > ((float*)x.val)[i])
        {
            ftime = true;
            min = ((float*)x.val)[i];
        }
    }
    return ftime ? min : 0;
}
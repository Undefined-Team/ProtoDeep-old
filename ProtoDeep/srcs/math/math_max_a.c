#include "pd_main.h"

float   pd_math_max_a(pd_float_a x)
{
    float min;
    bool ftime = false;

    if (x.type != PD_T_FLOAT)
        return (0);
    for (size_t i = 0; i < x.len; i++)
    {
        if (!ftime || min < ((float*)x.val)[i])
        {
            ftime = true;
            min = ((float*)x.val)[i];
        }
    }
    return ftime ? min : 0;
}
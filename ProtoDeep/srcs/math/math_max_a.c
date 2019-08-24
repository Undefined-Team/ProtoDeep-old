#include "pd_main.h"

float   math_max_a(t_farr x)
{
    float min;
    bool ftime = false;

    for (size_t i = 0; i < x.len; i++)
    {
        if (!ftime || min < x.arr[i])
        {
            ftime = true;
            min = x.arr[i];
        }
    }
    return ftime ? min : 0;
}
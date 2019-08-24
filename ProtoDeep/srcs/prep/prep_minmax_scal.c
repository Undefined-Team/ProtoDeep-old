#include "pd_main.h"

t_farr   prep_minmax_scal(t_farr x)
{
    t_farr y;
    float min;
    float maxsmin;

    min = math_min_a(x);
    maxsmin = math_max_a(x) - min;
    y = dast_new_farr(x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = (x.arr[i] - min) / maxsmin;
    }
    return y;
}
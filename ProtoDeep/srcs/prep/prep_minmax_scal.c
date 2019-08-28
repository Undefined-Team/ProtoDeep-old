#include "pd_main.h"

t_float_a   prep_minmax_scal(t_float_a x)
{
    t_float_a y;
    float   min;
    float   maxsmin;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    min = math_min_a(x);
    maxsmin = math_max_a(x) - min;
    y = arrInit(T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)x.val)[i] - min) / maxsmin;
    return y;
}
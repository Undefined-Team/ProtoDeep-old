#include "pd_main.h"

pd_float_a   pd_prep_minmax_scal(pd_float_a x)
{
    pd_float_a y;
    float   min;
    float   maxsmin;

    PD_PROT_ARR_TYPE(x.type, PD_T_FLOAT);
    min = pd_math_min_a(x);
    maxsmin = pd_math_max_a(x) - min;
    y = pd_arrInit(PD_T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)x.val)[i] - min) / maxsmin;
    return y;
}
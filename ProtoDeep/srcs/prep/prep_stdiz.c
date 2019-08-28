#include "pd_main.h"

t_float_a   prep_minmax_scal_stdiz(t_float_a x, t_prep_data pdata)
{
    t_float_a y;
    float som;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    som = 0;
    y = arrInit(T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        ((float*)y.val)[i] = (((float*)x.val)[i] - pdata.min) / pdata.maxsmin;
        som += ((float*)y.val)[i];
    }
    return y;
}

t_float_a   prep_minmax_scal_stdiz_init(t_float_a x, t_prep_data *pdata)
{
    t_float_a y;
    float som;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    som = 0;
    pdata->min = math_min_a(x);
    pdata->maxsmin = math_max_a(x) - pdata->min;
    y = arrInit(T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        ((float*)y.val)[i] = (((float*)x.val)[i] - pdata->min) / pdata->maxsmin;
        som += ((float*)y.val)[i];
    }
    pdata->mean = som / x.len;
    return y;
}

t_float_a   prep_stdiz(t_float_a x, t_prep_data pdata)
{
    t_float_a y;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    y = prep_minmax_scal_stdiz(x, pdata);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata.mean) / pdata.std_dev;
    return y;
}

t_float_a   prep_stdiz_init(t_float_a x, t_prep_data *pdata)
{
    t_float_a y;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    y = prep_minmax_scal_stdiz_init(x, pdata);
    pdata->std_dev = math_stdev(y, pdata->mean);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata->mean) / pdata->std_dev;
    return y;
}
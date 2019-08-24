#include "pd_main.h"

t_farr   prep_minmax_scal_stdiz(t_farr x, t_prep_data pdata)
{
    t_farr y;
    float som;

    som = 0;
    y = dast_new_farr(x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = (x.arr[i] - pdata.min) / pdata.maxsmin;
        som += y.arr[i];
    }
    return y;
}

t_farr   prep_minmax_scal_stdiz_init(t_farr x, t_prep_data *pdata)
{
    t_farr y;
    float som;

    som = 0;
    pdata->min = math_min_a(x);
    pdata->maxsmin = math_max_a(x) - pdata->min;
    y = dast_new_farr(x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = (x.arr[i] - pdata->min) / pdata->maxsmin;
        som += y.arr[i];
    }
    pdata->mean = som / x.len;
    return y;
}

t_farr   prep_stdiz(t_farr x, t_prep_data pdata)
{
    t_farr y;

    y = prep_minmax_scal_stdiz(x, pdata);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = (y.arr[i] - pdata.mean) / pdata.std_dev;
    }
    return y;
}

t_farr   prep_stdiz_init(t_farr x, t_prep_data *pdata)
{
    t_farr y;

    y = prep_minmax_scal_stdiz_init(x, pdata);
    pdata->std_dev = math_stdev(y, pdata->mean);
    for (size_t i = 0; i < y.len; i++)
    {
        y.arr[i] = (y.arr[i] - pdata->mean) / pdata->std_dev;
    }
    return y;
}
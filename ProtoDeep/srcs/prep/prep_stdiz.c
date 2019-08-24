#include "pd_main.h"

float   *prep_minmax_scal_stdiz(float *x, size_t len, t_prep_data pdata)
{
    float *y;
    float som;

    som = 0;
    y = malloc(sizeof(float) * len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (x[i] - pdata.min) / pdata.maxsmin;
        som += y[i];
    }
    return y;
}

float   *prep_minmax_scal_stdiz_init(float *x, size_t len, t_prep_data *pdata)
{
    float *y;
    float som;

    som = 0;
    pdata->min = math_min_a(x, len);
    pdata->maxsmin = math_max_a(x, len) - pdata->min;
    y = malloc(sizeof(float) * len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (x[i] - pdata->min) / pdata->maxsmin;
        som += y[i];
    }
    pdata->mean = som / len;
    return y;
}

float   *prep_stdiz(float *x, size_t len, t_prep_data pdata)
{
    float *y;

    y = prep_minmax_scal_stdiz(x, len, pdata);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (y[i] - pdata.mean) / pdata.std_dev;
    }
    return y;
}

float   *prep_stdiz_init(float *x, size_t len, t_prep_data *pdata)
{
    float *y;

    y = prep_minmax_scal_stdiz_init(x, len, pdata);
    pdata->std_dev = math_stdev(y, len, pdata->mean);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (y[i] - pdata->mean) / pdata->std_dev;
    }
    return y;
}
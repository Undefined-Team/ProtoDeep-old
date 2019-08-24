#include "pd_main.h"

float   *prep_minmax_scal_stdiz(float *x, size_t len, float *mean)
{
    float *y;
    float xmax;
    float xmin;
    float som;

    som = 0;
    xmax = math_max_a(x, len);
    xmin = math_min_a(x, len);
    y = malloc(sizeof(float) * len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (x[i] - xmin) / (xmax - xmin);
        som += y[i];
    }
    *mean = som / len;
    return y;
}

float   *prep_stdiz(float *x, size_t len, t_prep_data pdata)
{
    float *y;

    y = prep_minmax_scal(x, len);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (y[i] - pdata.mean) / pdata.std_dev;
    }
    return y;
}

float   *prep_stdiz_init(float *x, size_t len, t_prep_data *pdata)
{
    float *y;

    y = prep_minmax_scal_stdiz(x, len, &(pdata->mean));
    pdata->std_dev = math_stdev(y, len, pdata->mean);
    for (size_t i = 0; i < len; i++)
    {
        y[i] = (y[i] - pdata->mean) / pdata->std_dev;
    }
    return y;
}
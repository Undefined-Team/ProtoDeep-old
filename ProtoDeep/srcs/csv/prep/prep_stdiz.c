#include "pd_main.h"

t_float_a   prep_minmax_scal_stdiz(t_float_a x, t_stdiz_data pdata)
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

t_float_a   prep_minmax_scal_stdiz_init(t_float_a x, t_stdiz_data *pdata)
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

t_float_a   prep_stdiz(t_float_a x, t_stdiz_data pdata)
{
    t_float_a y;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    y = prep_minmax_scal_stdiz(x, pdata);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata.mean) / pdata.std_dev;
    arrFree(x);
    return y;
}

t_float_a   prep_stdiz_init(t_float_a x, t_stdiz_data *pdata)
{
    t_float_a y;

    PROT_ARR_TYPE(x.type, T_FLOAT);
    y = prep_minmax_scal_stdiz_init(x, pdata);
    pdata->std_dev = math_stdev(y, pdata->mean);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata->mean) / pdata->std_dev;
    arrFree(x);
    return y;
}

void        prep_standardize(t_csv csv, t_stdiz_a std_data)
{
    size_t i = 0;

    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == T_FLOAT)
            col->columns = prep_stdiz(col->columns, ((t_stdiz_data*)std_data.val)[i]);
        i++;
    }
}

t_stdiz_a    prep_strandardize_init(t_csv csv)
{
    size_t i = 0;

    t_stdiz_a new_std_data = arrInit(T_STDIZ, csv.width);
    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == T_FLOAT)
            col->columns = prep_stdiz_init(col->columns, &(((t_stdiz_data*)new_std_data.val)[i]));
        i++;
    }
    return new_std_data;
}
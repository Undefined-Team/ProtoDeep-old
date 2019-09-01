#include "pd_main.h"

pd_float_a   pd_prep_minmax_scal_stdiz(pd_float_a x, pd_stdiz_data pdata)
{
    pd_float_a y;
    float som;

    PD_PROT_ARR_TYPE(x.type, PD_T_FLOAT);
    som = 0;
    y = pd_arrInit(PD_T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        ((float*)y.val)[i] = (((float*)x.val)[i] - pdata.min) / pdata.maxsmin;
        som += ((float*)y.val)[i];
    }
    return y;
}

pd_float_a   pd_prep_minmax_scal_stdiz_init(pd_float_a x, pd_stdiz_data *pdata)
{
    pd_float_a y;
    float som;

    PD_PROT_ARR_TYPE(x.type, PD_T_FLOAT);
    som = 0;
    pdata->min = pd_math_min_a(x);
    pdata->maxsmin = pd_math_max_a(x) - pdata->min;
    y = pd_arrInit(PD_T_FLOAT, x.len);
    for (size_t i = 0; i < y.len; i++)
    {
        ((float*)y.val)[i] = (((float*)x.val)[i] - pdata->min) / pdata->maxsmin;
        som += ((float*)y.val)[i];
    }
    pdata->mean = som / x.len;
    return y;
}

pd_float_a   pd_prep_stdiz(pd_float_a x, pd_stdiz_data pdata)
{
    pd_float_a y;

    PD_PROT_ARR_TYPE(x.type, PD_T_FLOAT);
    y = pd_prep_minmax_scal_stdiz(x, pdata);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata.mean) / pdata.std_dev;
    pd_arrFree(x);
    return y;
}

pd_float_a   pd_prep_stdiz_init(pd_float_a x, pd_stdiz_data *pdata)
{
    pd_float_a y;

    PD_PROT_ARR_TYPE(x.type, PD_T_FLOAT);
    y = pd_prep_minmax_scal_stdiz_init(x, pdata);
    pdata->std_dev = pd_math_stdev(y, pdata->mean);
    for (size_t i = 0; i < y.len; i++)
        ((float*)y.val)[i] = (((float*)y.val)[i] - pdata->mean) / pdata->std_dev;
    pd_arrFree(x);
    return y;
}

void        pd_prep_standardize(pd_csv csv, pd_stdiz_a std_data)
{
    size_t i = 0;

    for (pd_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == PD_T_FLOAT)
            col->columns = pd_prep_stdiz(col->columns, ((pd_stdiz_data*)std_data.val)[i]);
        i++;
    }
}

pd_stdiz_a    pd_prep_strandardize_init(pd_csv csv)
{
    size_t i = 0;

    pd_stdiz_a new_std_data = pd_arrInit(PD_T_STDIZ, csv.width);
    for (pd_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == PD_T_FLOAT)
            col->columns = pd_prep_stdiz_init(col->columns, &(((pd_stdiz_data*)new_std_data.val)[i]));
        i++;
    }
    return new_std_data;
}
#include "pd_main.h"

void    prep_prepare(t_csv *csv, t_csv_conf *conf)
{
    prep_delete(csv, conf->delete_indexs);
    prep_ohe(csv, conf->ohe_indexs);
    prep_all_to_float(*csv);
    if (conf->std_data.len == 0)
    {
        t_stdiz_a tmp = conf->std_data;
        conf->std_data = prep_strandardize_init(*csv);
        arrFree(tmp);
    }
    else
        prep_standardize(*csv, conf->std_data);
}
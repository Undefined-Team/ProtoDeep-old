#include "pd_main.h"

void    pd_prep_prepare(pd_csv *csv, pd_csv_conf *conf)
{
    pd_prep_delete(csv, conf->delete_indexs);
    if (!conf->saved_trees)
        conf->saved_trees = pd_prep_ohe_init(csv, conf->ohe_indexs);
    else
        pd_prep_ohe(csv, conf->saved_trees);
    pd_prep_all_to_float(*csv);
    if (conf->std_data->len == 0)
    {
        pd_stdiz_a *tmp = conf->std_data;
        conf->std_data = pd_prep_strandardize_init(*csv);
        pd_arr_free(tmp);
    }
    else
        pd_prep_standardize(*csv, conf->std_data);
}
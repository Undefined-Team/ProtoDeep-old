#include "pd_main.h"

void    prep_prepare(t_csv *csv, t_csv_conf *conf)
{
    prep_delete(csv, conf->delete_indexs);
    dbug_print_csv(*csv);
    if (!conf->saved_trees)
        conf->saved_trees = prep_ohe_init(csv, conf->ohe_indexs);
    else
        prep_ohe(csv, conf->saved_trees);
    dbug_print_csv(*csv);
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
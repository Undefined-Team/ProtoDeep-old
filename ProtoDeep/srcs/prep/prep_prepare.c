#include "pd_main.h"

void    prep_prepare(t_csv *csv, t_csv_conf *conf)
{
    prep_ohe_delete(csv, conf->ohe_indexs, conf->delete_indexs);
    dbug_print_csv(*csv);
    prep_all_to_float(csv);
    dbug_print_csv(*csv);
    prep_standardize(csv, conf);
}
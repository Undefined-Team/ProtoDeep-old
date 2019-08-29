#include "pd_main.h"

void    prep_prepare(t_csv *csv, t_csv_conf *conf)
{
    printf("AHA %zd\n", ((t_arr*)csv->begin->columns.val)[0].len);
    prep_ohe_delete(csv, conf->ohe_indexs, conf->delete_indexs);
    printf("AHA2 %zd\n", ((t_arr*)csv->begin->columns.val)[0].len);
    dbug_print_csv(*csv);
    prep_all_to_float(csv);
    prep_standardize(csv, conf);
}
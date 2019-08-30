#include "pd_main.h"

t_csv_conf      prep_init_conf(t_str_a delete_indexs, t_str_a ohe_indexs)
{
    t_csv_conf new_conf;

    new_conf.delete_indexs = delete_indexs;
    new_conf.ohe_indexs = ohe_indexs;
    new_conf.std_data.len = 0;
    return new_conf;
}

void    prep_free_conf(t_csv_conf conf)
{
    strFree(conf.delete_indexs);
    strFree(conf.ohe_indexs);
    arrFree(conf.std_data);
}
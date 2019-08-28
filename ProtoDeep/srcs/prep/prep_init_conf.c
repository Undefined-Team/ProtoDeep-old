#include "pd_main.h"

t_csv_conf      prep_init_conf(t_size_t_a delete_indexs, t_size_t_a ohe_indexs)
{
    t_csv_conf new_conf;

    new_conf.delete_indexs = delete_indexs;
    new_conf.ohe_indexs = ohe_indexs;
    new_conf.std_data.len = 0;
    return new_conf;
}
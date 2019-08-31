#include "pd_main.h"

t_csv_conf      prep_init_conf(t_str_a delete_indexs, t_str_a ohe_indexs)
{
    t_csv_conf new_conf;

    new_conf.delete_indexs = delete_indexs;
    new_conf.ohe_indexs = ohe_indexs;
    new_conf.std_data.len = 0;
    new_conf.saved_trees = NULL;
    return new_conf;
}

void            prep_free_conf(t_csv_conf conf)
{
    strFree(conf.delete_indexs);
    strFree(conf.ohe_indexs);
    arrFree(conf.std_data);
    t_ohe_trees *tmp = conf.saved_trees;
    while (tmp)
    {
        conf.saved_trees = tmp;
        tmp = tmp->next;
        arrRFree(conf.saved_trees->base_name, -1);
        arrRFree(conf.saved_trees->new_names, -1);
        dast_free_tbnode(conf.saved_trees->begin);
        dast_free((void**)&conf.saved_trees);
    }    
}
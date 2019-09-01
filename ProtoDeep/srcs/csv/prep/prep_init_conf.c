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

void            prep_free_ohe_tree(t_ohe_trees *ohe_trees)
{
    t_ohe_trees *tmp = ohe_trees;
    while (tmp)
    {
        ohe_trees = tmp;
        tmp = tmp->next;
        arrRFree(ohe_trees->base_name, -1);
        arrRFree(ohe_trees->new_names, -1);
        prep_free_tbnode(ohe_trees->begin);
        dast_free((void**)&ohe_trees);
    }   
}

void            prep_free_conf(t_csv_conf conf)
{
    strFree(conf.delete_indexs);
    strFree(conf.ohe_indexs);
    arrFree(conf.std_data);
    prep_free_ohe_tree(conf.saved_trees);
}
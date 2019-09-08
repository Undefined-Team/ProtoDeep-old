#include "pd_main.h"

pd_csv_conf      pd_prep_init_conf(pd_str_a *delete_indexs, pd_str_a *ohe_indexs)
{
    pd_csv_conf new_conf;

    new_conf.delete_indexs = delete_indexs;
    new_conf.ohe_indexs = ohe_indexs;
    new_conf.std_data = pd_arr_new(PD_T_STDIZ, 0, NULL);
    new_conf.saved_trees = NULL;
    return new_conf;
}

void            pd_prep_free_ohe_tree(pd_ohe_trees *ohe_trees)
{
    pd_ohe_trees *tmp = ohe_trees;
    while (tmp)
    {
        ohe_trees = tmp;
        tmp = tmp->next;
        pd_arr_free_r(ohe_trees->base_name, -1);
        pd_arr_free_r(ohe_trees->new_names, -1);
        pd_prep_free_tbnode(ohe_trees->begin);
        pd_free(ohe_trees);
    }   
}

void            pd_prep_free_conf(pd_csv_conf conf)
{
    pd_str_free(conf.delete_indexs);
    pd_str_free(conf.ohe_indexs);
    pd_arr_free(conf.std_data);
    pd_prep_free_ohe_tree(conf.saved_trees);
}
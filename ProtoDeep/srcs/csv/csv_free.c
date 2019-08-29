#include "pd_main.h"

void    csv_free(t_csv csv)
{
    t_csv_col *before;

    for(t_csv_col *col = csv.begin; col; col = col->next)
    {
        before = col;
        col = col->next;
        dast_csv_free_col(before);
    }
}

void    csv_conf_free(t_csv_conf conf)
{
    arrFree(conf.delete_indexs);
    arrFree(conf.ohe_indexs);
    arrFree(conf.std_data);
}
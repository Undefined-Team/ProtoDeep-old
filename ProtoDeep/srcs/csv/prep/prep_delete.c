#include "pd_main.h"

void    pd_prep_delete(pd_csv *csv, pd_str_a *col_names)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    pd_csv_col   *col = csv->begin;
    size_t      i = 0;
    pd_csv_col   *before = NULL;
    pd_csv_col   *tmp = NULL;

    col_names = pd_prep_name_sort(*csv, col_names);
    while (col && i < col_names->len)
    {
        if (pd_str_cmp((char*)col->name.val, (char*)(((pd_str_a**)col_names->val)[i].val) ) == 0)
        {
            tmp = col;
            col = col->next;
            if (before)
                before->next = col;
            else
                csv->begin = col;
            pd_csv_free_col(tmp);
            i++;
        }
        if (!col)
            break;
        before = col;
        col = col->next;
    }
    i = 0;
    for (col = csv->begin; col; col = col->next)
        i++;
    csv->width = i;
    pd_arr_free(col_names);
}
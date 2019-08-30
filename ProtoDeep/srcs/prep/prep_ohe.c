#include "pd_main.h"

t_csv_col *cols_generator(t_csv_col **col, t_ohe_trees *tbegin)
{
    t_arr           str_arr = (*col)->columns;
    t_csv_col       *begin_col = NULL;
    t_csv_col       *last_col = NULL;
    t_csv_col       *f_tmp = *col;
    int             index;

    *col = (*col)->next;
    for (size_t i = 0; i < tbegin->new_names.len; i++)
    {
        last_col = prep_add_col(last_col, str_arr.len, 0, strSNew((char*)(((t_char_a*)tbegin->new_names.val)[i].val)));
        if (!begin_col)
            begin_col = last_col;
    }
    for (size_t i = 0; i < str_arr.len; i++)
    {
        index = use_bin_tree(tbegin, (char*)(((t_char_a*)str_arr.val)[i].val));
        prep_add_line(begin_col, index == -1 ? tbegin->new_names.len : (size_t)index, i);
    }
    last_col->next = *col;
    arrRFree(f_tmp->columns, -1);
    dast_free((void**)&f_tmp);
    return begin_col;
}

void    prep_ohe(t_csv *csv, t_ohe_trees *tbegin)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    t_csv_col   *col = csv->begin;
    size_t      i = 0;
    t_csv_col   *before = NULL;
    t_csv_col   *tmp = NULL;

    while (col && tbegin)
    {
        if (col->columns.type == T_STR && str_cmp((char*)col->name.val, ((char*)tbegin->base_name.val) ) == 0)
        {

            tmp = cols_generator(&col, tbegin); //col = last new, tmp = first new
            if (before)
                before->next = tmp;
            else
                csv->begin = tmp;
            tbegin = tbegin->next;
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
}
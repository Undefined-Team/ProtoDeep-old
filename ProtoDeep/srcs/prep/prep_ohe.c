#include "pd_main.h"

char        *name()

void        add_line(t_csv_col *begin_col, size_t col_index, size_t line_index)
{
    size_t i = -1;
    
    while (begin_col)
    {
        begin_col->columns->farr[line_index] = col_index == i ? 1 : 0;
        begin_col = begin_col->next;
    }
}

t_csv_col   add_col(t_csv_col last_col, size_t nbr_line, size_t max_line, t_carr name)
{
    if (!last_col)
        last_col = dast_csv_new_col(CSV_FLOAT, nbr_line, name);
    else
    {
        last_col->next = dast_csv_new_col(CSV_FLOAT, nbr_line, name);
        last_col = last_col->next;
    }
    for (int i = 0; i < max_line - 1; i++)
        last_col->columns->arr[i] = 0;
    return last_col;
}

t_carr      update_bin_tree(tbnode *tbegin, char *name, int *new_index)
{

}

t_csv_col *cols_generator(t_csv_col **col)
{
    t_tbnode        *tbegin = dast_new_tbnode('x');
    t_starr         *str_arr = *col->columns->arr;
    t_csv_col       *begin_col = NULL;
    t_csv_col       *last_col = NULL;
    t_csv_col       *f_tmp;
    char            *name;
    size_t           new_index;

    f_tmp = *col;
    *col = *col->next;
    for (size_t i = 0; i < str_arr.len; i++)
    {
        name = update_bin_tree(tbegin, str_arr.arr[i], &new_index);
        if (!name)
            add_line(begin_col, new_index, i);
        else
        {
            last_col = add_col(last_col, str_arr.len, i, name);
            if (!begin_col)
                begin_col = last_col;
            add_line(begin_col, new_index, i);
        }
    }
    last_col->next = *col;
    free_col(f_tmp);
    return begin_col;
}

void    prep_ohe(t_csv_col *col, t_siarr col_indexs)
{
    // Error if col is not of type t_carr
    // Error if indexs in col_indexs is out of range
    int j = 0;
    int i = -1;
    t_csv_col *before = NULL;

    math_sort_siarr(&col_indexs);
    while (j < col_indexs.len)
    {
        while (++i < col_indexs.arr[j])
        {
            before = col;
            col = col->next;
        }
        //col = prep_ohe_col(col, before);
        before->next = cols_generator(&col);
    }

}
#include "pd_main.h"

int        pd_use_bin_tree(pd_tbnode *node, char *str)
{
    for (pd_tbnode *f_begin = node->f_begin; f_begin; f_begin = f_begin->next)
    {
        if (f_begin->c == *str)
        {
            if (*(str + 1) == '\0') // If it's the last char
                return f_begin->word_index;
            else
                return use_bin_tree(f_begin, ++str);
        }
    }
    return -1;
}

static pd_csv_col *pd_cols_generator(pd_csv_col **col, pd_ohe_trees *tbegin)
{
    pd_arr           str_arr = (*col)->columns;
    pd_csv_col       *begin_col = NULL;
    pd_csv_col       *last_col = NULL;
    pd_csv_col       *f_tmp = *col;
    int             index;

    *col = (*col)->next;
    for (size_t i = 0; i < tbegin->new_names.len; i++)
    {
        last_col = pd_prep_add_col(last_col, str_arr.len, 0, pd_strSNew((char*)(((t_char_a*)tbegin->new_names.val)[i].val)));
        if (!begin_col)
            begin_col = last_col;
    }
    for (size_t i = 0; i < str_arr.len; i++)
    {
        index = pd_use_bin_tree(tbegin->begin, (char*)(((t_char_a*)str_arr.val)[i].val));
        pd_prep_add_line(begin_col, index == -1 ? tbegin->new_names.len : (size_t)index, i);
    }
    last_col->next = *col;
    pd_csv_free_col(f_tmp);
    return begin_col;
}

void    pd_prep_ohe(pd_csv *csv, pd_ohe_trees *tbegin)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    pd_csv_col   *col = csv->begin;
    size_t      i = 0;
    pd_csv_col   *before = NULL;
    pd_csv_col   *tmp = NULL;

    while (col && tbegin)
    {
        if (col->columns.type == T_STR && pd_str_cmp((char*)col->name.val, ((char*)tbegin->base_name.val) ) == 0)
        {
            tmp = pd_cols_generator(&col, tbegin); //col = last new, tmp = first new
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
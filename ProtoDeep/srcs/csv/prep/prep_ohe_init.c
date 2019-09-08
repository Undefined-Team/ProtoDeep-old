#include "pd_main.h"

void        pd_prep_add_line(pd_csv_col *begin_col, size_t col_index, size_t line_index)
{
    size_t i = 0;
    
    while (begin_col)
    {
        ((float*)begin_col->columns->val)[line_index] = col_index == i++ ? 1 : 0;
        begin_col = begin_col->next;
    }
}

pd_csv_col   *pd_prep_add_col(pd_csv_col *last_col, size_t nbr_line, size_t max_line, pd_char_a *name)
{
    if (!last_col)
        last_col = pd_csv_new_col(pd_arr_init(PD_T_FLOAT, nbr_line), name);
    else
    {
        last_col->next = pd_csv_new_col(pd_arr_init(PD_T_FLOAT, nbr_line), name);
        last_col = last_col->next;
    }
    for (size_t i = 0; i < max_line; i++)
        ((float*)last_col->columns->val)[i] = 0;
    return last_col;
}

pd_char_a      *pd_found_word(pd_tbnode *f_begin, int *new_index, int *total_index)
{
    *total_index = *total_index + 1;
    f_begin->word_index = *total_index;
    *new_index = *total_index;
    return pd_str_char_to_str(f_begin->c);
}

pd_char_a      *pd_update_bin_tree(pd_tbnode *node, char *str, int *new_index, int *total_index)
{
    pd_tbnode    *f_begin = node->f_begin;
    pd_tbnode    *tmp = NULL;
    pd_char_a    *result;

    while (f_begin)
    {
        if (f_begin->c == *str)
        {
            if (*(str + 1) == '\0') // If it's the last char
            {
                if (f_begin->word_index == -1) // Ex : Found new word franc in francais
                    return (pd_found_word(f_begin, new_index, total_index));                           
                *new_index = f_begin->word_index; // Ex : Found old word franc in francais
                return pd_str_new_s("");
            }
            else
            {
                result = pd_update_bin_tree(f_begin, ++str, new_index, total_index);
                return result->len == 0 ? result : pd_str_fjoin(pd_str_char_to_str(f_begin->c), result);  // Go deeper
            }
        }
        tmp = f_begin;
        f_begin = f_begin->next;
    }
    // Add new node to binary tree
    if (!node->f_begin) // Child list empty
    {
        node->f_begin = pd_prep_new_tbnode(*str, -1); // Create first child
        f_begin = node->f_begin;
    }
    else
    {
        tmp->next = pd_prep_new_tbnode(*str, -1); // Add child
        f_begin = tmp->next;
    }
    if (*(str + 1) == '\0') // If it's the last char
        return (pd_found_word(f_begin, new_index, total_index)); // Ex found new world francais by franc ?
    result = pd_update_bin_tree(f_begin, ++str, new_index, total_index);
    return result->len == 0 ? result : pd_str_fjoin(pd_str_char_to_str(f_begin->c), result);  // Go deeper
}

pd_ohe_trees *pd_new_ohe_tree(pd_char_a *base_name, pd_csv_col *begin, int len, pd_tbnode *tbegin)
{
    pd_ohe_trees *new;

    PD_PROT_MALLOC(new = pd_malloc(sizeof(pd_ohe_trees)));
    new->base_name = base_name;
    new->begin = tbegin;
    new->new_names = pd_arr_init(PD_T_STR, len);
    new->next = NULL;
    size_t i = 0;
    for (; begin; begin = begin->next)
        ((pd_char_a**)new->new_names->val)[i++] = pd_str_new_s((char*)begin->name->val); // ATTENTION ON LE FREE
    return new;
}

static pd_csv_col *pd_cols_generator(pd_csv_col **col, pd_ohe_trees **t_tmp)
{
    pd_tbnode        *tbegin = pd_prep_new_tbnode('\0', -2);
    pd_arr           *str_arr = (*col)->columns;
    pd_csv_col       *begin_col = NULL;
    pd_csv_col       *last_col = NULL;
    pd_csv_col       *f_tmp = *col;
    pd_char_a        *name;
    int             new_index;
    int             total_index = -1;

    *col = (*col)->next;
    for (size_t i = 0; i < str_arr->len; i++)
    {
        name = pd_update_bin_tree(tbegin, (char*)(((pd_char_a**)str_arr->val)[i]->val), &new_index, &total_index);
        if (name->len == 0)
        {
            pd_prep_add_line(begin_col, new_index, i);
            pd_arr_free(name);
        }
        else
        {
            last_col = pd_prep_add_col(last_col, str_arr->len, i, name);
            if (!begin_col)
                begin_col = last_col;
            pd_prep_add_line(begin_col, new_index, i);
        }
    }
    if (!(*t_tmp))
        *t_tmp = pd_new_ohe_tree(f_tmp->name, begin_col, total_index + 1, tbegin);
    else
        (*t_tmp)->next = pd_new_ohe_tree(f_tmp->name, begin_col, total_index + 1, tbegin);
    last_col->next = *col;
    pd_arr_free_r(f_tmp->columns, -1);
    pd_free(f_tmp);
    return begin_col;
}

pd_ohe_trees    *pd_prep_ohe_init(pd_csv *csv, pd_str_a *col_names)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    pd_csv_col   *col = csv->begin;
    size_t      i = 0;
    pd_csv_col   *before = NULL;
    pd_csv_col   *tmp = NULL;
    pd_ohe_trees *begin = NULL;
    pd_ohe_trees *t_tmp = NULL;

    col_names = pd_prep_name_sort(*csv, col_names);
    while (col && i < col_names->len)
    {
        if (col->columns->type == PD_T_STR && pd_str_cmp((char*)col->name->val, (char*)(((pd_str_a**)col_names->val)[i]->val) ) == 0)
        {
            if (!begin)
            {
                tmp = pd_cols_generator(&col, &begin); //col = last new, tmp = first new
                t_tmp = begin;
            }
            else
            {
                tmp = pd_cols_generator(&col, &t_tmp); //col = last new, tmp = first new
                t_tmp = t_tmp->next;
            }
            if (before)
                before->next = tmp;
            else
                csv->begin = tmp;
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
    return begin;
}
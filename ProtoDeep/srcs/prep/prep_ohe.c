#include "pd_main.h"

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

t_carr      found_word(tbnode *f_begin, int *new_index, int *total_index)
{
    *total_index = *total_index + 1;
    f_begin->word_index = *total_index;
    *new_index = *total_index;
    return (str_char_to_str(f_begin->c));
}

t_carr      update_bin_tree(tbnode *node, char *str, int *new_index, int *total_index)
{
    t_tbnode *f_begin = node->front_begin;
    t_tbnode *tmp = NULL;
    t_carr    result;

    while (f_begin)
    {
        if (f_begin->c == *str)
        {
            if (*(str + 1) == NULL) // If it's the last char
            {
                if (f_begin->word_index == -1) // Ex : Found new word franc in francais
                    return (found_word(f_begin, new_index, total_index));                           
                *new_index = f_begin->word_index; // Ex : Found old word franc in francais
                return dast_new_static_carr("", 0);
            }
            else
            {
                result = update_bin_tree(f_begin, str++, new_index, total_index);
                return (result.len == 0 ? result : str_add_char(result, f_begin->c));  // Go deeper
            }
        }
        tmp = f_begin;
        f_begin = f_begin->next;
    }
    if (!node->front_begin) // Child list empty
    {
        node->front_begin = dast_new_tbnode('a', -1); // Create first child
        f_begin = node->front_begin;
    }
    else
    {
        tmp->next = dast_new_tbnode('a', -1); // Add child
        f_begin = tmp->next;
    }
    if (*(str + 1) == NULL) // If it's the last char
        return (found_word(f_begin, new_index, total_index));
    result = update_bin_tree(f_begin, str++, new_index, total_index);
    return (result.len == 0 ? result : str_add_char(result, f_begin->c));  // Go deeper
}

t_csv_col *cols_generator(t_csv_col **col)
{
    t_tbnode        *tbegin = dast_new_tbnode(NULL, -2);
    t_starr         *str_arr = *col->columns->arr;
    t_csv_col       *begin_col = NULL;
    t_csv_col       *last_col = NULL;
    t_csv_col       *f_tmp;
    char            *name;
    size_t          *new_index;
    size_t          *total_index;

    f_tmp = *col;
    *col = *col->next;
    for (size_t i = 0; i < str_arr.len; i++)
    {
        name = update_bin_tree(tbegin, str_arr.arr[i], &new_index, &total_index);
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

    math_si_sort(col_indexs);
    while (j < col_indexs.len)
    {
        while (++i < col_indexs.arr[j])
        {
            before = col;
            col = col->next;
        }
        before->next = cols_generator(&col);
    }
}

/*
Taches :
-  | str_add_char
-  | str_char_to_str
- math_sort_siarr
- sbedene dst_new_col faut la regarder
- Gerer erreur de type
- Gerer erreur de index dans col
*/
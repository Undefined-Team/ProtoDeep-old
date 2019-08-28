#include "pd_main.h"

void        add_line(t_csv_col *begin_col, size_t col_index, size_t line_index)
{
    size_t i = 0;
    
    while (begin_col)
    {
        ((float*)begin_col->columns.val)[line_index] = col_index == i++ ? 1 : 0;
        begin_col = begin_col->next;
    }
}

t_csv_col   *add_col(t_csv_col *last_col, size_t nbr_line, size_t max_line, t_str name)
{
    if (!last_col)
        last_col = dast_csv_new_col(dast_init_arr(T_FLOAT, nbr_line), name);
    else
    {
        last_col->next = dast_csv_new_col(dast_init_arr(T_FLOAT, nbr_line), name);
        last_col = last_col->next;
    }
    for (size_t i = 0; i < max_line; i++)
        ((float*)last_col->columns.val)[i] = 0;
    return last_col;
}

t_str      found_word(t_tbnode *f_begin, int *new_index, int *total_index)
{
    *total_index = *total_index + 1;
    f_begin->word_index = *total_index;
    *new_index = *total_index;
    return (str_char_to_str(f_begin->c));
}

t_str      update_bin_tree(t_tbnode *node, char *str, int *new_index, int *total_index)
{
    t_tbnode *f_begin = node->f_begin;
    t_tbnode *tmp = NULL;
    t_str    result;

    while (f_begin)
    {
        if (f_begin->c == *str)
        {
            if (*(str + 1) == '\0') // If it's the last char
            {
                if (f_begin->word_index == -1) // Ex : Found new word franc in francais
                    return (found_word(f_begin, new_index, total_index));                           
                *new_index = f_begin->word_index; // Ex : Found old word franc in francais
                return strSNew("");
            }
            else
            {
                result = update_bin_tree(f_begin, ++str, new_index, total_index);
                return result.len == 0 ? result : str_fjoin(str_char_to_str(f_begin->c), result);  // Go deeper
            }
        }
        tmp = f_begin;
        f_begin = f_begin->next;
    }
    if (!node->f_begin) // Child list empty
    {
        node->f_begin = dast_new_tbnode(*str, -1); // Create first child
        f_begin = node->f_begin;
    }
    else
    {
        tmp->next = dast_new_tbnode(*str, -1); // Add child
        f_begin = tmp->next;
    }
    if (*(str + 1) == '\0') // If it's the last char
        return (found_word(f_begin, new_index, total_index));
    result = update_bin_tree(f_begin, ++str, new_index, total_index);
    return result.len == 0 ? result : str_fjoin(str_char_to_str(f_begin->c), result);  // Go deeper
}


t_csv_col *cols_generator(t_csv_col **col)
{
    t_tbnode        *tbegin = dast_new_tbnode('\0', -2);
    t_arr           str_arr = (*col)->columns;
    t_csv_col       *begin_col = NULL;
    t_csv_col       *last_col = NULL;
    t_csv_col       *f_tmp;
    t_str           name;
    int             new_index;
    int             total_index = -1;

    f_tmp = *col;
    *col = (*col)->next;
    for (size_t i = 0; i < str_arr.len; i++)
    {
        name = update_bin_tree(tbegin, (char*)(((t_str*)str_arr.val)[i].val), &new_index, &total_index);
        if (name.len == 0)
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
    (void)f_tmp;
    //free_col(f_tmp); ATTENTION FAUT FAIRE CETTE FONCTION QUI PEUT CLEAN UN PEUT TOUT
    return begin_col;
}

void    prep_ohe(t_csv *csv, t_arr col_indexs)
{
    // Error if col is not of type t_carr
    // Error if indexs in col_indexs is out of range
    t_csv_col   *col = csv->begin;
    size_t      i = 0;
    t_csv_col   *before = NULL;
    t_csv_col   *tmp = NULL;

    math_si_sort(col_indexs);
    for (size_t j = 0; j < col_indexs.len; j++)
    {
        while (i++ < ((size_t*)col_indexs.val)[j] && col)
        {
            before = col;
            col = col->next;
        }
        if (col->columns.type == T_STR)
        {
            tmp = cols_generator(&col);
            if (before)
                before->next = tmp->next;
            else
                csv->begin = tmp->next;
            //free_col(tmp);
        }
    }
    i = 0;
    for (col = csv->begin; col; col = col->next)
        i++;
    csv->width = i;
}

/*
Taches :
-  | str_add_char
-  | str_char_to_str
-  | math_sort_siarr
-  | sbedene dst_new_col faut la regarder
-  | Gerer erreur de type
- Gerer erreur de index dans col
- Faire la fonction de free
*/
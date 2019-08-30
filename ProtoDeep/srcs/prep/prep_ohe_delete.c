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

t_csv_col   *add_col(t_csv_col *last_col, size_t nbr_line, size_t max_line, t_char_a name)
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

t_char_a      found_word(t_tbnode *f_begin, int *new_index, int *total_index)
{
    *total_index = *total_index + 1;
    f_begin->word_index = *total_index;
    *new_index = *total_index;
    return str_char_to_str(f_begin->c);
}

t_char_a      update_bin_tree(t_tbnode *node, char *str, int *new_index, int *total_index)
{
    t_tbnode    *f_begin = node->f_begin;
    t_tbnode    *tmp = NULL;
    t_char_a    result;

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
    // Add new node to binary tree
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
        return (found_word(f_begin, new_index, total_index)); // Ex found new world francais by franc ?
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
    t_char_a        name;
    int             new_index;
    int             total_index = -1;

    f_tmp = *col;
    *col = (*col)->next;
    for (size_t i = 0; i < str_arr.len; i++)
    {
        name = update_bin_tree(tbegin, (char*)(((t_char_a*)str_arr.val)[i].val), &new_index, &total_index);
        if (name.len == 0)
        {
            add_line(begin_col, new_index, i);
            arrFree(name);
        }
        else
        {
            last_col = add_col(last_col, str_arr.len, i, name);
            if (!begin_col)
                begin_col = last_col;
            add_line(begin_col, new_index, i);
        }
    }
    last_col->next = *col;
    dast_csv_free_col(f_tmp);
    dast_free_tbnode(tbegin);
    return begin_col;
}

void    prep_ohe_delete(t_csv *csv, t_str_a col_names, bool del_ohe)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    t_csv_col   *col = csv->begin;
    size_t      i = 0;
    t_csv_col   *before = NULL;
    t_csv_col   *tmp = NULL;

    col_names = dast_name_sort(*csv, col_names);
    while (col && i < col_names.len)
    {
        if (str_cmp((char*)col->name.val, (char*)(((t_str_a*)col_names.val)[i].val) ) == 0)
        {
            if (del_ohe)
            {
                tmp = col;
                col = col->next;
                if (before)
                    before->next = col;
                else
                    csv->begin = col;
                dast_csv_free_col(tmp);
            }
            else if (col->columns.type == T_STR)
            {
                tmp = cols_generator(&col); //col = last new, tmp = first new
                if (before)
                    before->next = tmp;
                else
                    csv->begin = tmp;
            }
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
    //dast_free((void**)&col_names.val);
    arrFree(col_names);
}

/*

- Faire que *col = last_col pour mieux utiliser les i et economiser des lignes
- Sauvegarder l arbre binaire dans conf
- Faire une fonction d utilisation de l arbre binaire (Si un mot n est pas trouve alors 0 dans chaque ligne)

*/
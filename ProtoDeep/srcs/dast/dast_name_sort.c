#include "pd_main.h"

t_name_index *dast_new_ni(t_char_a name, size_t index)
{
    t_name_index *elem = NULL;

    PROT_MALLOC(elem = malloc(sizeof(t_name_index)));
    elem->name = name;
    elem->index = index;
    elem->next = NULL;
    return elem;
}

t_str_a  dast_name_sort(t_csv csv, t_str_a col_ni)
{
    size_t real_size = 0;
    t_name_index *begin = NULL;
    t_name_index *tmp = NULL;
    size_t j = 0;

    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        for (size_t i = 0; i < col_ni.len; i++)
        {
            if (str_cmp( (char*)(((t_str_a*)col_ni.val)[i].val), (char*)col->name.val ) == 0)
            {
                if (!begin)
                {
                    begin = dast_new_ni(((t_char_a*)col_ni.val)[i], j);
                    tmp = begin;
                }
                else
                {
                    tmp->next =  dast_new_ni(((t_char_a*)col_ni.val)[i], j);
                    tmp = tmp->next;
                }
                real_size++;
                break;
            }
        }
        j++;
    }

    tmp = begin;
    t_size_t_a index_a = arrInit(T_SIZE_T, real_size);
    for (size_t i = 0; i < real_size; i++)
    {
        ((size_t*)index_a.val)[i] = tmp->index;
        tmp = tmp->next; 
    }
    math_si_sort(index_a);
    t_str_a new_col_ni = arrInit(T_STR, real_size);
    for (size_t i = 0; i < real_size; i++)
    {
        for (tmp = begin; tmp; tmp = tmp->next)
        {
            if (((size_t*)index_a.val)[i] == tmp->index)
            {
                ((t_str_a*)new_col_ni.val)[i] = tmp->name;
                break;
            }
        }
    }
    while (begin)
    {
        tmp = begin;
        begin = begin->next;
        dast_free((void**)&tmp);
    }
    arrFree(index_a);
    return new_col_ni;
}
#include "pd_main.h"

pd_name_index *pd_prep_new_ni(pd_char_a *name, size_t index)
{
    pd_name_index *elem = NULL;

    PD_PROT_MALLOC(elem = pd_malloc(sizeof(pd_name_index)));
    elem->name = name;
    elem->index = index;
    elem->next = NULL;
    return elem;
}

pd_str_a  *pd_prep_name_sort(pd_csv csv, pd_str_a *col_ni)
{
    size_t real_size = 0;
    pd_name_index *begin = NULL;
    pd_name_index *tmp = NULL;
    size_t j = 0;

    for (pd_csv_col *col = csv.begin; col; col = col->next)
    {
        for (size_t i = 0; i < col_ni->len; i++)
        {
            if (pd_str_cmp( (char*)(((pd_str_a*)col_ni->val)[i].val), (char*)col->name.val ) == 0)
            {
                if (!begin)
                {
                    begin = pd_prep_new_ni(((pd_char_a*)col_ni->val)[i], j);
                    tmp = begin;
                }
                else
                {
                    tmp->next =  pd_prep_new_ni(((pd_char_a*)col_ni->val)[i], j);
                    tmp = tmp->next;
                }
                real_size++;
                break;
            }
        }
        j++;
    }

    tmp = begin;
    pd_size_t_a *index_a = pd_arr_init(PD_T_SIZE_T, real_size);
    for (size_t i = 0; i < real_size; i++)
    {
        ((size_t*)index_a->val)[i] = tmp->index;
        tmp = tmp->next; 
    }
    pd_math_si_sort(index_a);
    pd_str_a *new_col_ni = pd_arr_init(PD_T_STR, real_size);
    for (size_t i = 0; i < real_size; i++)
    {
        for (tmp = begin; tmp; tmp = tmp->next)
        {
            if (((size_t*)index_a->val)[i] == tmp->index)
            {
                ((pd_str_a*)new_col_ni->val)[i] = tmp->name;
                break;
            }
        }
    }
    while (begin)
    {
        tmp = begin;
        begin = begin->next;
        pd_free(tmp);
    }
    pd_arr_free(index_a);
    return new_col_ni;
}
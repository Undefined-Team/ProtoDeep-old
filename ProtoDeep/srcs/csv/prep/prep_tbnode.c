#include "pd_main.h"

t_tbnode  *prep_new_tbnode(char c, int word_index)
{
    t_tbnode *new_node;

    PROT_MALLOC(new_node = malloc(sizeof(t_tbnode)))
    new_node->next = NULL;
    new_node->f_begin = NULL;
    new_node->f_last = NULL;
    new_node->c = c;
    new_node->word_index = word_index;
    return new_node;
}

void    prep_free_tbnode(t_tbnode *begin)
{
    t_tbnode *lst = begin->f_begin;
    t_tbnode *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        prep_free_tbnode(tmp);
    }
    dast_free((void**)&begin);
}
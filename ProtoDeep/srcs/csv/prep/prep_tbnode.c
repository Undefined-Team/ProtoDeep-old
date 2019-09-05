#include "pd_main.h"

pd_tbnode  *pd_prep_new_tbnode(char c, int word_index)
{
    pd_tbnode *new_node;

    PD_PROT_MALLOC(new_node = pd_malloc(sizeof(pd_tbnode)))
    new_node->next = NULL;
    new_node->f_begin = NULL;
    new_node->f_last = NULL;
    new_node->c = c;
    new_node->word_index = word_index;
    return new_node;
}

void    pd_prep_free_tbnode(pd_tbnode *begin)
{
    pd_tbnode *lst = begin->f_begin;
    pd_tbnode *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        pd_prep_free_tbnode(tmp);
    }
    pd_free(begin);
}
#include "pd_main.h"

t_tbnode  *dast_new_tbnode(char c)
{
    t_tbnode *new_node;

    PROT_MALLOC(new_node = malloc(sizeof(t_tbnode)))
    new_node->next = NULL;
    new_node->f_first = NULL;
    new_node->f_last = NULL;
    new_node->c = c;
    new_node->word_index = -1;
    return new_node;
}


#include "pd_main.h"

pd_arr  *pd_str_fjoin(pd_arr *head, pd_arr *tail)
{
    pd_arr *new_str;
    
    new_str = pd_str_join(head, tail);
    if (head->val)
        pd_arr_free(head);
    if (tail->val)
        pd_arr_free(tail);
    return (new_str);
}
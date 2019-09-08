#include "pd_main.h"

pd_arr  *pd_str_fjoin(pd_arr *head, pd_arr *tail)
{
    pd_arr *new_str;
    
    new_str = pd_str_join(head, tail);
    if (head->val)
        pd_free(head->val);
    if (tail->val)
        pd_free(tail->val);
    return (new_str);
}
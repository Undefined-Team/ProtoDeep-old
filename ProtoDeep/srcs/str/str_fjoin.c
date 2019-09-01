#include "pd_main.h"

pd_arr  pd_str_fjoin(pd_arr head, pd_arr tail)
{
    pd_arr new_str;
    
    new_str = str_join(head, tail);
    if (head.val)
        pd_dast_free((void**)&head.val);
    if (tail.val)
        pd_dast_free((void**)&tail.val);
    return (new_str);
}
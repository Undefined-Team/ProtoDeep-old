#include "pd_main.h"

t_arr  str_fjoin(t_arr head, t_arr tail)
{
    t_arr new_str;
    
    new_str = str_join(head, tail);
    if (head.val)
        dast_free((void**)&head.val);
    if (tail.val)
        dast_free((void**)&tail.val);
    return (new_str);
}
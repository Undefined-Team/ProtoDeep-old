#include "pd_main.h"

t_arr  str_fsub(t_arr str, size_t start, size_t length)
{
    t_arr new_str;
    
    new_str = str_sub(str, start, length);
    if (str.val)
        dast_free((void**)&str.val);
    return (new_str);
}
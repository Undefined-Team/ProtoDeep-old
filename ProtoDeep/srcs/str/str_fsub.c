#include "pd_main.h"

pd_arr  pd_str_fsub(pd_arr str, size_t start, size_t length)
{
    pd_arr new_str;
    
    new_str = pd_str_sub(str, start, length);
    if (str.val)
        pd_dast_free((void**)&str.val);
    return (new_str);
}
#include "pd_main.h"

pd_arr      pd_arr_shape_concat(pd_arr a, pd_arr b)
{
    pd_arr      c = pd_arr_init(a.type, a.len + b.len);
    if (a.type == PD_T_FLOAT)
        for (size_t i = 0; i < a.len; i++) ((float *)c.val)[i] = ((float *)a.val)[i];
    else if (a.type == PD_T_SIZE_T)
        for (size_t i = 0; i < a.len; i++) ((size_t *)c.val)[i] = ((size_t *)a.val)[i];
    else if (a.type == PD_T_CHAR)
        for (size_t i = 0; i < a.len; i++) ((char *)c.val)[i] = ((char *)a.val)[i];
    if (a.type == PD_T_FLOAT)
        for (size_t i = a.len; i < a.len + b.len; i++) ((float *)c.val)[i] = ((float *)b.val)[i - a.len];
    else if (a.type == PD_T_SIZE_T)
        for (size_t i = a.len; i < a.len + b.len; i++) ((size_t *)c.val)[i] = ((size_t *)b.val)[i - a.len];
    else if (a.type == PD_T_CHAR)
        for (size_t i = a.len; i < a.len + b.len; i++) ((char *)c.val)[i] = ((char *)b.val)[i - a.len];
    return (c);
}
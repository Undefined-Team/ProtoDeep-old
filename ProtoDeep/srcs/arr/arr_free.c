#include "pd_main.h"

void    pd_arr_free_r(pd_arr arr, int depth)
{
    if (arr.type == PD_T_ARR && (depth > 0 || depth == -1))
    {
        for (size_t i = 0; i < arr.len; i++)
            pd_arr_free_r(((pd_arr*)arr.val)[i], depth == -1 ? -1 : depth -1);
    }
    pd_free(arr.val);
}
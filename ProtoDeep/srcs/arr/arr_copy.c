#include "pd_main.h"

pd_arr      pd_arr_copy(pd_arr array)
{
    pd_arr new_array;

    new_array = pd_arr_init(array.type, array.len);
    if (array.type == PD_T_ARR)
    {
        for (size_t i = 0; i < array.len; i++)
            ((pd_arr*)new_array.val)[i] = pd_arr_copy(((pd_arr*)array.val)[i]);
    }
    else if (array.type == PD_T_FLOAT)
        pd_mem_cpy(new_array.val, array.val, sizeof(float) * array.len);
    else if (array.type == PD_T_SIZE_T)
        pd_mem_cpy(new_array.val, array.val, sizeof(size_t) * array.len);
    else if (array.type == PD_T_CHAR)
        pd_mem_cpy(new_array.val, array.val, sizeof(char) * array.len);
    else
        pd_error("last type must be float, size_t or char");
    return new_array;
}
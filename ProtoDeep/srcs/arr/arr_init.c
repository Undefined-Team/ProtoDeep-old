#include "pd_main.h"

pd_arr       pd_arr_init(pd_type type, size_t len)
{
    pd_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == PD_T_ARR)
            new_arr.val = pd_malloc(sizeof(pd_arr) * len);
        else if (type == PD_T_FLOAT)
            new_arr.val = pd_malloc(sizeof(float) * len);
        else if (type == PD_T_SIZE_T)
            new_arr.val = pd_malloc(sizeof(size_t) * len);
        else if (type == PD_T_STDIZ)
            new_arr.val = pd_malloc(sizeof(pd_stdiz_data) * len);
        else if (type == PD_T_CHAR)
            new_arr.val = pd_malloc(sizeof(char) * (len + 1));
        if (!new_arr.val)
            new_arr.len = 0;
    }
    if (type == PD_T_CHAR && len == 0)
    {
        new_arr.val = pd_malloc(sizeof(char));
        ((char *)new_arr.val)[0] = 0;
    }
    return new_arr;
}
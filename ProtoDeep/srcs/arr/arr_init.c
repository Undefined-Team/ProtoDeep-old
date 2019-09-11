#include "pd_main.h"

pd_arr       *pd_arr_init(pd_type type, size_t len)
{
    pd_arr *new_arr;

    new_arr = pd_arr_new(type, len, NULL);
    if (len > 0)
    {
        if (type == PD_T_ARR)
        {
            new_arr->val = pd_malloc(sizeof(pd_arr *) * len);
            //for (size_t i = 0; i < new_arr->len; i++)
            //    ((pd_arr**)new_arr->val)[i] = pd_arr_new(type, len, NULL);
        }
        else if (type == PD_T_FLOAT) new_arr->val = pd_malloc(sizeof(float) * len);
        else if (type == PD_T_SIZE_T) new_arr->val = pd_malloc(sizeof(size_t) * len);
        else if (type == PD_T_STDIZ) new_arr->val = pd_malloc(sizeof(pd_stdiz_data) * len);
        else if (type == PD_T_CHAR) new_arr->val = pd_malloc(sizeof(char) * (len + 1));
        if (!new_arr->val) new_arr->len = 0;
    }
    if (type == PD_T_CHAR && len == 0)
    {
        new_arr->val = pd_malloc(sizeof(char));
        ((char *)new_arr->val)[0] = 0;
    }
    return new_arr;
}

pd_arr      *pd_arr_init_z(pd_type type, size_t len)
{
    size_t i = 0;
    pd_arr *new_arr = pd_arr_init(type, len);
    if (type == PD_T_FLOAT) for (; i < len; i++) ((float*)new_arr->val)[i] = 0;
    else if (type == PD_T_SIZE_T) for (; i < new_arr->len; i++) ((size_t*)new_arr->val)[i] = 0;
    else if (type == PD_T_CHAR) for (; i < new_arr->len; i++) ((char*)new_arr->val)[i] = '\0';
    else pd_error("type must be PD_T_FLOAT or PD_T_SIZE_T or PD_T_CHAR");
    return new_arr;
}
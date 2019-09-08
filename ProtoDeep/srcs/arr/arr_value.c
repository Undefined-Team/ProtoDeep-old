#include "pd_main.h"

void        *pd_arr_return_value(pd_arr arr, va_list *va)
{
    size_t index = (size_t)va_arg(*va, int);
    va_end(*va);
    if (index > arr.len)
        pd_error("Index (%zd) out of range (%zd)", index, arr.len - 1);
    if (arr.type == PD_T_FLOAT)
        return (&((float *)arr.val)[index]);
    else if (arr.type == PD_T_SIZE_T)
    {
        // printf("%zd\n", ((size_t *)arr.val)[index]);
        return (&((size_t *)arr.val)[index]);
    }
    else if (arr.type == PD_T_CHAR)
        return (&((char *)arr.val)[index]);
    else
        pd_error("Wrong type");
}

void        *pd_arr_value_ctr(pd_arr arr, va_list *va)
{
    if (arr.type == PD_T_ARR)
    {
        size_t index = (size_t)va_arg(*va, int);
        if (index > arr.len)
            pd_error("Index (%zd) out of range (%zd)", index, arr.len - 1);
        return (pd_arr_value_ctr(((pd_arr *)arr.val)[index], va));
    }
    else
    {
        return (pd_arr_return_value(arr, va));
    }
}

size_t      pd_arr_value(pd_arr arr, pd_type type, ...)
{
    va_list va;
    size_t  value;

    va_start(va, type);
    if (type == PD_T_FLOAT)
        value = *(float *)pd_arr_value_ctr(arr, &va);
    else if (type == PD_T_SIZE_T)
        value = *(size_t *)pd_arr_value_ctr(arr, &va);
    else if (type == PD_T_CHAR)
        value = *(char *)pd_arr_value_ctr(arr, &va);
    va_end(va);
    return (value);
}
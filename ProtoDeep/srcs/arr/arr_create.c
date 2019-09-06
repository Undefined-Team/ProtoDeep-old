#include "pd_main.h"

pd_arr      pd_arr_create_ctr(size_t *arr_shape, size_t rank, pd_type type, va_list *va)
{
    if (rank > 1)
    {
        pd_arr new_arr = pd_arr_init(PD_T_ARR, arr_shape[0]);
        for (size_t i = 0; i < new_arr.len; i++)
        {
            ((pd_arr *)new_arr.val)[i] = pd_arr_create_ctr(&arr_shape[1], rank - 1, type, va);
        }
        return (new_arr);
    }
    else
    {
        pd_arr values = pd_arr_init(type, arr_shape[0]);
        if (type == PD_T_FLOAT)
            for (size_t i = 0; i < values.len; i++) ((float *)values.val)[i] = (float)va_arg(*va, double);
        else if (type == PD_T_SIZE_T)
            for (size_t i = 0; i < values.len; i++) ((size_t *)values.val)[i] = (size_t)va_arg(*va, unsigned int);
        else if (type == PD_T_CHAR)
            for (size_t i = 0; i < values.len; i++) ((char *)values.val)[i] = (char)va_arg(*va, int);
        else if (type == PD_T_STR)
        {
            for (size_t i = 0; i < values.len; i++)
            {
                char *buffer = va_arg(*va, char *);
                size_t len = pd_str_clen(buffer);
                pd_str_a str = pd_arr_init(PD_T_CHAR, len);
                str.val = buffer;
                ((pd_arr *)values.val)[i] = str;
            }
        }
        return (values);
    }
}

size_t      pd_arr_get_shape_len(pd_size_t_a arr_shape)
{
    size_t  len = 1;
    
    for (size_t i = 0; i < arr_shape.len; i++)
        len *= ((size_t *)arr_shape.val)[i];
    return (len);
}

pd_arr      pd_arr_create(pd_size_t_a arr_shape, pd_type type, ...)
{
    pd_arr  new_arr;
    va_list va;
    size_t  len;

    va_start(va, type);
    len = pd_arr_get_shape_len(arr_shape);
    new_arr = pd_arr_init(PD_T_ARR, ((size_t *)arr_shape.val)[0]);
    for (size_t i = 0; i < new_arr.len; i++)
        ((pd_arr *)new_arr.val)[i] = pd_arr_create_ctr(&((size_t *)arr_shape.val)[1], arr_shape.len - 1, type, &va);
    return (new_arr);
}
#include "pd_main.h"

static void        pd_arr_create_get_values(pd_arr *arr, pd_type type, va_list *va)
{
    if (type == PD_T_FLOAT)
        for (size_t i = 0; i < arr->len; i++) ((float *)arr->val)[i] = (float)va_arg(*va, double);
    else if (type == PD_T_SIZE_T)
        for (size_t i = 0; i < arr->len; i++) ((size_t *)arr->val)[i] = (size_t)va_arg(*va, unsigned int);
    else if (type == PD_T_CHAR)
        for (size_t i = 0; i < arr->len; i++) ((char *)arr->val)[i] = (char)va_arg(*va, int);
    else if (type == PD_T_STR)
    {
        for (size_t i = 0; i < arr->len; i++)
        {
            char *buffer = va_arg(*va, char *);
            size_t len = pd_str_clen(buffer);
            pd_str_a str = pd_arr_init(PD_T_CHAR, len);
            str.val = buffer;
            ((pd_arr *)arr->val)[i] = str;
        }
    }
    else
        pd_error("Last type must be float, size_t, char or str (in pd_arr_create).");
}

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
        pd_arr_create_get_values(&values, type, va);
        return (values);
    }
}

pd_arr      pd_arr_create(pd_size_t_a arr_shape, pd_type type, ...)
{
    pd_arr  new_arr;
    va_list va;

    va_start(va, type);
    if (arr_shape.len == 1)
    {
        new_arr = pd_arr_init(type, ((size_t *)arr_shape.val)[0]);
        pd_arr_create_get_values(&new_arr, type, &va);
        va_end(va);
		pd_arr_free(arr_shape);
        return (new_arr);
    }
    new_arr = pd_arr_init(PD_T_ARR, ((size_t *)arr_shape.val)[0]);
    for (size_t i = 0; i < new_arr.len; i++)
        ((pd_arr *)new_arr.val)[i] = pd_arr_create_ctr(&((size_t *)arr_shape.val)[1], arr_shape.len - 1, type, &va);
    va_end(va);
	pd_arr_free(arr_shape);
    return (new_arr);
}

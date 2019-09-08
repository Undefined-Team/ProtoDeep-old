#include "pd_main.h"

static void        pd_arr_create_get_values(pd_arr *arr, pd_type type, va_list *va)
{
    if (type == PD_T_FLOAT)
    {
        float *t_arr_val = (float *)arr->val;
        for (size_t i = 0; i < arr->len; i++) t_arr_val[i] = (float)va_arg(*va, double);
    }
    else if (type == PD_T_SIZE_T)
    {
        size_t *t_arr_val = (size_t *)arr->val;
        for (size_t i = 0; i < arr->len; i++) t_arr_val[i] = (size_t)va_arg(*va, unsigned int);
    }
    else if (type == PD_T_CHAR)
    {
        char *t_arr_val = (char *)arr->val;
        for (size_t i = 0; i < arr->len; i++) t_arr_val[i] = (char)va_arg(*va, int);
    }
    else if (type == PD_T_STR)
    {
        pd_arr **t_arr_val = (pd_arr **)arr->val;
        for (size_t i = 0; i < arr->len; i++)
        {
            char *buffer = va_arg(*va, char *);
            pd_str_a *str = pd_str_new_s(buffer);
            t_arr_val[i] = str;
        }
    }
    else
        pd_error("Last type must be float, size_t, char or str (in pd_arr_create).");
}

pd_arr      *pd_arr_create_ctr(size_t *arr_shape, size_t rank, pd_type type, va_list *va)
{
    if (rank > 1)
    {
        pd_arr *new_arr = pd_arr_init(PD_T_ARR, arr_shape[0]);
        pd_arr **t_new_arr_val = (pd_arr **)new_arr->val;
        for (size_t i = 0; i < new_arr->len; i++)
            t_new_arr_val[i] = pd_arr_create_ctr(&arr_shape[1], rank - 1, type, va);
        return (new_arr);
    }
    else
    {
        pd_arr *values = pd_arr_init(type, arr_shape[0]);
        pd_arr_create_get_values(values, type, va);
        return (values);
    }
}

pd_arr      *pd_arr_create(pd_size_t_a *arr_shape, pd_type type, ...)
{
    pd_arr  *new_arr;
    va_list va;

    va_start(va, type);
    if (arr_shape->len == 1)
    {
        new_arr = pd_arr_init(type, ((size_t *)arr_shape->val)[0]);
        pd_arr_create_get_values(new_arr, type, &va);
        va_end(va);
		pd_arr_free(arr_shape);
        return (new_arr);
    }
    new_arr = pd_arr_init(PD_T_ARR, ((size_t *)arr_shape->val)[0]);
    pd_arr **t_new_arr_val = (pd_arr **)new_arr->val;
    size_t *t_arr_shape_val = (size_t *)arr_shape->val;
    for (size_t i = 0; i < new_arr->len; i++)
        t_new_arr_val[i] = pd_arr_create_ctr(&t_arr_shape_val[1], arr_shape->len - 1, type, &va);
    va_end(va);
	pd_arr_free(arr_shape);
    return (new_arr);
}

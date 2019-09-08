#include "pd_main.h"

size_t      pd_tens_flatten_len(pd_tensor *tensor)
{
    size_t      nb_values = 1;
    size_t      *t_shape_val = (size_t *)tensor->shape->val;

    for (size_t i = 0; i < tensor->shape->len; i++)
        nb_values *= t_shape_val[i];
    return (nb_values);
}

void    pd_tens_get_values(pd_tensor *tensor, size_t *index, pd_tensor *flat)
{
    if (tensor->rank > 1)
    {
        pd_tensor **t_tensor_val = (pd_tensor **)tensor->val;
        for (size_t i = 0; i < tensor->len; i++)
            pd_tens_get_values(t_tensor_val[i], index, flat);
    }
    else
    {
        float *t_flat_val = (float *)flat->val;
        float *t_tensor_val = (float *)tensor->val;
        for (size_t i = 0; i < tensor->len; i++)
            t_flat_val[(*index)++] = t_tensor_val[i];
    }
}

pd_tensor   *pd_tens_flatten(pd_tensor *tensor)
{
    pd_tensor   *flat;
    pd_size_t_a *len;
    size_t      index = 0;

    index = 0;
    len = pd_arr_init(PD_T_SIZE_T, 1);
    ((size_t *)len->val)[0] = pd_tens_flatten_len(tensor);
    flat = pd_tens_init(len);
    pd_tens_get_values(tensor, &index, flat);
    return (flat);
}
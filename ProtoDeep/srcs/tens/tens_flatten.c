#include "pd_main.h"

int         pd_tens_flatten_len(pd_tensor tensor)
{
    size_t      nb_values = 1;

    for (size_t i = 0; i < tensor.shape.len; i++)
        nb_values *= ((size_t *)tensor.shape.val)[i];
    return (nb_values);
}

void    pd_tens_get_values(pd_tensor tensor, size_t *index, pd_tensor *flat)
{
    if (tensor.rank > 1)
        for (size_t i = 0; i < tensor.len; i++)
            pd_tens_get_values(((pd_tensor *)tensor.val)[i], index, flat);
    else
        for (size_t i = 0; i < tensor.len; i++)
            ((float *)flat->val)[(*index)++] = ((float *)tensor.val)[i];
}

pd_tensor   pd_tens_flatten(pd_tensor tensor)
{
    pd_tensor   flat;
    size_t      *len;
    size_t      index = 0;

    len = pd_malloc(1 * sizeof(size_t));
    len[0] = pd_tens_flatten_len(tensor);
    flat = pd_tens_init(len, 1);
    pd_tens_get_values(tensor, &index, &flat);
    return (flat);
}
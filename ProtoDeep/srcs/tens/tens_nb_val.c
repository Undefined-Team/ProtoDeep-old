#include "pd_main.h"

size_t      pd_tens_nb_val(pd_tensor *tensor)
{
    size_t      nb_values = 1;
    size_t      *t_shape_val = tensor->shape;
    size_t      len = tensor->shape_len;

    for (size_t i = 0; i < len; i++)
        nb_values *= t_shape_val[i];
    return (nb_values);
}
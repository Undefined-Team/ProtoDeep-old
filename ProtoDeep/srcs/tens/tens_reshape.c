#include "pd_main.h"

int         pd_tens_check_size(pd_tensor tensor, pd_size_t_a shape)
{
    size_t      shape_values = 1;
    size_t      tensor_values = 1;

    for (size_t i = 0; i < shape.len; i++)
        shape_values *= ((size_t *)shape.val)[i];
    for (size_t i = 0; i < tensor.shape.len; i++)
        tensor_values *= ((size_t *)tensor.shape.val)[i];
    return (shape_values == tensor_values);
}

pd_tensor   pd_tens_reshape(pd_tensor tensor, pd_size_t_a shape)
{
    pd_tensor   tensor;
}
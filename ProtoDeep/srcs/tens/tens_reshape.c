#include "pd_main.h"

void    pd_tens_check_size(pd_tensor tensor, pd_size_t_a *shape)
{
    size_t      shape_values = 1;
    size_t      tensor_values = 1;
    size_t      neg = 0;
    size_t      neg_idx = 0;
    size_t      *t_shape_val = (size_t *)shape->val;

    for (size_t i = 0; i < shape->len; i++)
        if (t_shape_val[i] == 0)
        {
            neg_idx = i;
            if (neg++)
                pd_error("New shape can only have 0 once.");
        }
        else
            shape_values *= t_shape_val[i];
    size_t *t_tensor_shape_val = (size_t *)tensor.shape.val;
    for (size_t i = 0; i < tensor.shape.len; i++)
        tensor_values *= t_tensor_shape_val[i];
    if (neg && shape_values)
    {
        size_t infered = tensor_values / shape_values;
        if (tensor_values == shape_values * infered)
        {
            ((size_t *)shape->val)[neg_idx] = infered;
            shape_values *= infered;
        }
        if (shape_values != tensor_values)
            pd_error("Can't find valid shape by replacing \'0\' value (%zd values in tensor, %zd values in shape).\n", tensor_values, shape_values);
    }
    if (shape_values != tensor_values)
        pd_error("Can't reshape tensor with %zd values to shape with %zd values.\n", tensor_values, shape_values);
}

void    pd_tens_reshape_from_flat(pd_tensor flat, size_t *index, pd_tensor *reshape)
{
    if (reshape->rank > 1)
    {
        pd_tensor **t_reshape_val = (pd_tensor **)reshape->val;
        for (size_t i = 0; i < reshape->len; i++)
            pd_tens_reshape_from_flat(flat, index, t_reshape_val[i]);
    }
    else
    {
        float *t_reshape_val = (float *)reshape->val;
        float *t_flat_val = (float *)flat.val;
        for (size_t i = 0; i < reshape->len; i++)
            t_reshape_val[i] = t_flat_val[(*index)++];
    }
}

pd_tensor   *pd_tens_reshape(pd_tensor *tensor, pd_size_t_a shape)
{
    pd_tensor   *reshape;
    pd_tensor   *flat;
    size_t      index = 0;

    pd_tens_check_size(*tensor, &shape);
    reshape = pd_tens_init(shape);
    flat = pd_tens_flatten(tensor);
    pd_tens_reshape_from_flat(*flat, &index, reshape);
	pd_tens_free(flat);
    return (reshape);
}

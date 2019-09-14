#include "pd_main.h"

void    pd_tens_check_size(pd_tensor *tensor, pd_size_t_a *shape)
{
    size_t      shape_values = 1;
    size_t      tensor_values = 1;
    size_t      zero = 0;
    size_t      zero_idx = 0;
    size_t      *t_shape_val = (size_t *)shape->val;
    size_t      shape_len = shape->len;

    for (pd_count i = 0; i < shape_len; i++)
        if (!*t_shape_val)
        {
            zero_idx = i;
            if (zero++)
                pd_error("New shape can only have 0 once.");
            *t_shape_val++;
        }
        else
            shape_values *= *t_shape_val++;
    size_t *t_tensor_shape_val = tensor->shape;
    size_t tensor_shape_len = tensor->shape_len;
    for (pd_count i = 0; i < tensor_shape_len; i++)
        tensor_values *= *t_tensor_shape_val++;
    if (zero && shape_values)
    {
        size_t infered = tensor_values / shape_values;
        if (tensor_values == shape_values * infered)
        {
            ((size_t *)shape->val)[zero_idx] = infered;
            shape_values *= infered;
        }
        else if (shape_values != tensor_values)
            pd_error("Can't find valid shape by replacing \'0\' value (%zd values in tensor, %zd values in shape).\n", tensor_values, shape_values);
    }
    else if (shape_values != tensor_values)
        pd_error("Can't reshape tensor with %zd values to shape with %zd values.\n", tensor_values, shape_values);
}

pd_tensor   *pd_tens_reshape_cpy(pd_tensor *tensor, pd_size_t_a *shape)
{
    pd_tensor   *reshape;
    float       *t_tensor_val;
    float       *t_reshape_val;

    pd_tens_check_size(tensor, shape);
    reshape = pd_tens_init(shape);
    pd_mem_cpy(reshape->val, tensor->val, tensor->len * sizeof(float));
    return (reshape);
}

pd_tensor   *pd_tens_reshape(pd_tensor *tensor, pd_size_t_a *shape)
{
    pd_tens_check_size(tensor, shape);
    pd_free(tensor->shape);
    tensor->shape = (size_t *)shape->val;
    tensor->shape_len = shape->len;
    pd_free(tensor->shape_m);
    tensor->shape_m = pd_tens_shape_mult((size_t *)shape->val, shape->len);
    pd_free(shape);
    return (tensor);
}
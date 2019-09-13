#include "pd_main.h"

void    pd_tens_check_size(pd_tensor *tensor, pd_size_t_a *shape)
{
    size_t      shape_values = 1;
    size_t      tensor_values = 1;
    size_t      neg = 0;
    size_t      neg_idx = 0;
    size_t      *t_shape_val = (size_t *)shape->val;
    size_t      shape_len = shape->len;

    for (pd_count i = 0; i < shape_len; i++)
        if (!t_shape_val[i])
        {
            neg_idx = i;
            if (neg++)
                pd_error("New shape can only have 0 once.");
        }
        else
            shape_values *= t_shape_val[i];
    size_t *t_tensor_shape_val = tensor->shape;
    for (pd_count i = 0; i < tensor->shape_len; i++)
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

pd_tensor   *pd_tens_reshape(pd_tensor *tensor, pd_size_t_a *shape)
{
    pd_tensor   *reshape;
    float       *t_tensor_val;
    float       *t_reshape_val;

    pd_tens_check_size(tensor, shape);
    reshape = pd_tens_init(shape);
    t_tensor_val = tensor->val;
    t_reshape_val = reshape->val;
    size_t len = tensor->len;
    pd_mem_cpy(t_reshape_val, t_tensor_val, len * sizeof(float));
    return (reshape);
}

pd_tensor   *pd_tens_reshape_inplace(pd_tensor *tensor, pd_size_t_a *shape)
{
    pd_free(tensor->shape);
    tensor->shape = (size_t *)shape->val;
    tensor->shape_len = shape->len;
    pd_free(tensor->shape_m);
    tensor->shape_m = pd_get_shape_mult((size_t *)shape->val, shape->len, &tensor->len);
    pd_free(shape);
    return (tensor);
}
#include "pd_main.h"

pd_tensor pd_tens_rec_concat(pd_tensor tensor_a, pd_tensor tensor_b, size_t dim, size_t target_dim)
{
    size_t j = 0;
    pd_tensor new_tensor;

    new_tensor.shape.val = NULL;
    new_tensor.rank = tensor_a.rank;
    if (dim == target_dim)
    {
        new_tensor.len = tensor_a.len + tensor_b.len;
        if (dim > 0)
        {
            new_tensor.val = pd_malloc(sizeof(pd_tensor) * new_tensor.len);
            for (size_t i = 0; i < tensor_a.len; i++)
                ((pd_tensor*)new_tensor.val)[j++] = pd_tens_copy(((pd_tensor*)tensor_a.val)[i]);
            for (size_t i = 0; i < tensor_b.len; i++)
                ((pd_tensor*)new_tensor.val)[j++] = pd_tens_copy(((pd_tensor*)tensor_b.val)[i]);
        }
        else
        {
            new_tensor.val = pd_malloc(sizeof(float) * new_tensor.len);
            for (size_t i = 0; i < tensor_a.len; i++)
                ((float*)new_tensor.val)[j++] = ((float*)tensor_a.val)[i];
            for (size_t i = 0; i < tensor_b.len; i++)
                ((float*)new_tensor.val)[j++] = ((float*)tensor_b.val)[i];
        }
    }
    else
    {
        new_tensor.len = tensor_a.len;
        new_tensor.val = pd_malloc(sizeof(pd_tensor) * new_tensor.len);
        for (size_t i = 0; i < tensor_a.len; i++)
            ((pd_tensor*)new_tensor.val)[i] = pd_tens_rec_concat(((pd_tensor*)tensor_a.val)[i], ((pd_tensor*)tensor_b.val)[i], dim - 1, target_dim);
    }
    new_tensor.shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}

pd_tensor pd_tens_concat(pd_tensor tensor_a, pd_tensor tensor_b, int axis)
{
    if (tensor_a.rank != tensor_b.rank) pd_error("The ranks of the tensors are different");
    if (pd_math_abs(axis) >= tensor_a.rank) pd_error("The axis must be between -rank and rank (-rank < axis < rank)");
    if (axis < 0)
        axis = tensor_a.rank - axis;
    axis = (axis + 1) % tensor_a.rank;
    size_t new_shape[tensor_a.rank];
    for (size_t i = 0; i < tensor_a.rank; i++)
    {
        if (i != axis)
        {
            if (((size_t*)tensor_a.shape.val)[i] != ((size_t*)tensor_b.shape.val)[i]) return pd_tens_init(NULL, 0);
            new_shape[i] = ((size_t*)tensor_a.shape.val)[i];
        }
        else new_shape[i] = ((size_t*)tensor_a.shape.val)[i] + ((size_t*)tensor_b.shape.val)[i];
    }
    return pd_tens_rec_concat(tensor_a, tensor_b, tensor_b.rank - 1, (size_t)axis);
}
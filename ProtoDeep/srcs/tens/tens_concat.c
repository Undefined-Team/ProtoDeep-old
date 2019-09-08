#include "pd_main.h"

pd_tensor *pd_tens_rec_concat(pd_tensor *tensor_a, pd_tensor *tensor_b, size_t dim, size_t target_dim)
{
    size_t j = 0;
    pd_tensor *new_tensor;

    new_tensor = pd_tens_new(tensor_a->rank, 0, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
    if (dim == target_dim)
    {
        new_tensor->len = tensor_a->len + tensor_b->len;
        if (dim > 0)
        {
            pd_tensor **a_new_tensor = pd_malloc(sizeof(pd_tensor*) * new_tensor->len);
            new_tensor->val = a_new_tensor;
            pd_tensor **a_tensor_a = (pd_tensor**)tensor_a->val;
            pd_tensor **a_tensor_b = (pd_tensor**)tensor_b->val;
            for (size_t i = 0; i < tensor_a->len; i++)
                a_new_tensor[j++] = pd_tens_copy(a_tensor_a[i]);
            for (size_t i = 0; i < tensor_b->len; i++)
                a_new_tensor[j++] = pd_tens_copy(a_tensor_b[i]);
        }
        else
        {
            float *a_new_tensor = pd_malloc(sizeof(float) * new_tensor->len);
            new_tensor->val = a_new_tensor;
            float *a_tensor_a = (float*)tensor_a->val;
            float *a_tensor_b = (float*)tensor_b->val;
            for (size_t i = 0; i < tensor_a->len; i++)
                a_new_tensor[j++] = a_tensor_a[i];
            for (size_t i = 0; i < tensor_b->len; i++)
                a_new_tensor[j++] = a_tensor_b[i];
        }
    }
    else
    {
        new_tensor->len = tensor_a->len;
        pd_tensor **a_new_tensor = pd_malloc(sizeof(pd_tensor*) * new_tensor->len);
        new_tensor->val = a_new_tensor;
        pd_tensor **a_tensor_a = (pd_tensor**)tensor_a->val;
        pd_tensor **a_tensor_b = (pd_tensor**)tensor_b->val;
        for (size_t i = 0; i < tensor_a->len; i++)
            a_new_tensor[i] = pd_tens_rec_concat(a_tensor_a[i], a_tensor_b[i], dim - 1, target_dim);
    }
    new_tensor->shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}

pd_tensor *pd_tens_concat(pd_tensor *tensor_a, pd_tensor *tensor_b, int axis)
{
    if (tensor_a->rank != tensor_b->rank) pd_error("The ranks of the tensors are different");
    if (pd_math_abs(axis) >= tensor_a->rank) pd_error("The axis must be between -rank and rank (-rank < axis < rank)");
    if (axis < 0)
        axis = tensor_a->rank - axis;
    axis = (axis + 1) % tensor_a->rank;
    size_t new_shape[tensor_a->rank];
    size_t *a_shape_a = (size_t*)tensor_a->shape.val;
    size_t *a_shape_b = (size_t*)tensor_b->shape.val;
    for (size_t i = 0; i < tensor_a->rank; i++)
    {
        if ((int)i != axis)
        {
            if (a_shape_a[i] != a_shape_b[i]) return pd_tens_init(pd_arr_shape(0));
            new_shape[i] = a_shape_a[i];
        }
        else new_shape[i] = a_shape_a[i] + a_shape_b[i];
    }
    return pd_tens_rec_concat(tensor_a, tensor_b, tensor_b->rank - 1, (size_t)axis);
}
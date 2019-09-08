#include "pd_main.h"

static pd_size_t_a     *pd_get_new_shape(pd_size_t_a *shape, pd_size_t_a *new_dim, size_t *flat_len)
{
    size_t shape_len = shape->len;
    pd_size_t_a *new_shape = pd_arr_init(PD_T_SIZE_T, shape_len);
    size_t *a_new_shape = (size_t*)new_shape->val;
    size_t *a_shape = (size_t*)shape->val;
    size_t *a_new_dim = (size_t*)new_dim->val;
    size_t t_flat_len = 1;
    size_t t_shape_val;
    for (size_t i = 0; i < shape_len; i++)
    {
        t_shape_val = a_shape[a_new_dim[i]];
        a_new_shape[i] = t_shape_val;
        t_flat_len *= t_shape_val;
    }
    *flat_len = t_flat_len;
    return new_shape;
}

static size_t     *pd_get_shape_mult(pd_size_t_a *new_shape)
{
    size_t *a_new_shape = (size_t*)new_shape->val;
    size_t new_shape_len = new_shape->len;
    size_t *a_shape_mult = pd_malloc(sizeof(size_t) * new_shape_len);
    a_shape_mult[new_shape_len - 1] = 1;
    for (size_t i = new_shape_len - 1; i > 0; i--)
        a_shape_mult[i - 1] = a_new_shape[i] * a_shape_mult[i];
    return a_shape_mult;
}

static size_t          pd_get_index(size_t len, size_t *coord, size_t *new_dim, size_t *new_shape_mult)
{
    size_t index = 0;
    for (size_t i = 0; i < len; i++)
        index += coord[new_dim[i]] * new_shape_mult[i];
    return index;
}

static void            pd_update_value(pd_tensor *tensor, float *flatten, size_t coord_index, size_t *coord, size_t *new_dim, size_t *new_shape_mult)
{
    size_t tensor_len = tensor->len;
    if (tensor->rank == 1)
    {
        float *a_tensor = (float*)tensor->val;
        for (size_t i = 0; i < tensor_len; i++)
        {
            coord[coord_index] = i;
            flatten[pd_get_index(coord_index + 1, coord, new_dim, new_shape_mult)] = a_tensor[i];
        }
    }
    else
    {
        pd_tensor **a_tensor = (pd_tensor**)tensor->val;
        for (size_t i = 0; i < tensor_len; i++)
        {
            coord[coord_index] = i;
            pd_update_value(a_tensor[i], flatten, coord_index + 1, coord, new_dim, new_shape_mult);
        }
    }
}

pd_tensor       *pd_tens_transpose(pd_tensor *tensor, pd_size_t_a *new_dim)
{
    if (tensor->rank != new_dim->len) pd_error("There must be as many new dimensions as the rank of the tensor-> (tensor->rank == new_dim->len)");
    bool valid[new_dim->len];
    pd_mem_set(valid, false, sizeof(bool) * new_dim->len);
    size_t *t_new_dim = (size_t*)new_dim->val;
    size_t t_index;
    size_t new_dim_len = new_dim->len;
    for (size_t i = 0; i < new_dim_len; i++)
    {
        t_index = t_new_dim[i];
        if (t_index >= new_dim_len)
            pd_error("A dimension can't be greater than the number of dimensions (new_dim->val[i] < new_dim->length)");
        if (valid[t_index] == true)
            pd_error("2 dimensions can't have the same dimension");
        valid[t_index] = true;
    }
    size_t flat_len;
    pd_size_t_a *new_shape = pd_get_new_shape(tensor->shape, new_dim, &flat_len);
    size_t *new_shape_mult = pd_get_shape_mult(new_shape);
    pd_tensor *new_flatten = pd_tens_init(pd_arr_shape(1, flat_len));
    size_t *coord = pd_malloc(sizeof(size_t) * tensor->shape->len);
    pd_update_value(tensor, (float*)new_flatten->val, 0, coord, (size_t*)new_dim->val, new_shape_mult);
    pd_tensor *transpose_tensor = pd_tens_reshape(new_flatten, new_shape);
    pd_tens_free(new_flatten);
    pd_arr_free(new_dim);
    pd_free(new_shape_mult);
    pd_free(coord);
    return transpose_tensor;
}
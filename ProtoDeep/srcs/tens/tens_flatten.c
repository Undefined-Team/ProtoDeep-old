#include "pd_main.h"

pd_tensor   *pd_tens_flatten_copy(pd_tensor *tensor)
{
    pd_tensor   *flat;
    float       *t_tensor_val;
    pd_size_t_a *len;

    len = pd_arr_shape(1, tensor->len);
    flat = pd_tens_init(len);
    pd_mem_cpy(flat->val, tensor->val, flat->len * sizeof(float));
    return (flat);
}

pd_tensor   *pd_tens_flatten(pd_tensor *tensor)
{
    size_t *shape = pd_malloc(sizeof(size_t));
    *shape = tensor->len;
    pd_free(tensor->shape);
    tensor->shape = shape;
    pd_free(tensor->shape_m);
    size_t *shape_m = pd_malloc(sizeof(size_t));
    *shape_m = 1;
    tensor->shape_m = shape_m;
    tensor->shape_len = 1;
    tensor->len = *(tensor->shape);
    return (tensor);
}
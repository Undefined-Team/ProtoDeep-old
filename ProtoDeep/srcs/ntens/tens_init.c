#include "pd_main.h"

static size_t     *pd_get_shape_mult(size_t *shape, pd_count shape_len, size_t *len)
{
    size_t *a_shape_mult = pd_malloc(sizeof(size_t) * shape_len);
    --shape_len;
    a_shape_mult[shape_len] = 1;
    if (shape[0] == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
    size_t new_len = shape[0];
    for (pd_count i = shape_len; i > 0; --i)
    {
        if (a_shape[i] == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
        a_shape_mult[i - 1] = shape[i] * a_shape_mult[i];
        new_len *= shape[i];
    }
    *len = new_len;
    return a_shape_mult;
}

pd_ntensor *pd_ntens_init_val(pd_arr *shape, float new_val)
{
    pd_count shape_len = shape->len;
    if (shape_len == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t *a_shape = (size_t*)shape->val;

    pd_ntensor *new_tensor = pd_malloc(sizeof(pd_ntensor));
    new_tensor->shape = a_shape;
    new_tensor->shape_len = shape_len;
    size_t nbr_float;
    new_tensor->shape_m = pd_get_shape_mult(a_shape, shape_len, &nbr_float);
    new_tensor->len = nbr_float;
    float *val = pd_malloc(sizeof(float) * nbr_float);
    new_tensor->val = val;
    for (--nbr_float >= 0) *val-- = new_val;
    return new_tensor;
}
#include "pd_main.h"

size_t     *pd_get_shape_mult(size_t *shape, pd_count shape_len, size_t *len)
{
    size_t *shape_m;
    PD_PROT_MALLOC(shape_m = pd_malloc(sizeof(size_t) * shape_len));
    --shape_len;
    size_t *shape_m_tmp = &shape_m[shape_len];
    size_t *shape_m_tmp_2 = shape_m_tmp - 1;
    *shape_m_tmp = 1;
    if (*shape == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
    size_t new_len = *shape;
    shape = &shape[shape_len];
    for (pd_count i = shape_len; i > 0; --i)
    {
        if (*shape == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
        *shape_m_tmp_2 = *shape * *shape_m_tmp;
        new_len *= *shape--;
    }
    *len = new_len;
    return shape_m;
}

pd_tensor *pd_tens_init_ctr(size_t *shape, size_t shape_len)
{
    if (shape_len == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    pd_tensor *new_tensor;
    PD_PROT_MALLOC(new_tensor = pd_malloc(sizeof(pd_tensor)));
    new_tensor->shape = shape;
    new_tensor->shape_len = shape_len;
    new_tensor->shape_m = pd_get_shape_mult(shape, shape_len, &new_tensor->len);
    PD_PROT_MALLOC(new_tensor->val = pd_malloc(sizeof(float) * new_tensor->len));
    return new_tensor;
}

pd_tensor *pd_tens_init(pd_arr *shape)
{
    pd_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    pd_tensor *new_tensor = pd_tens_init_ctr(a_shape, shape_len);
    
    return new_tensor;
}

pd_tensor *pd_tens_init_val(pd_arr *shape, float new_val)
{
    pd_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    pd_tensor *new_tensor = pd_tens_init_ctr(a_shape, shape_len);
    
    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    while (len-- > 0) *val++ = new_val;
    return new_tensor;
}

pd_tensor *pd_tens_init_rand(pd_arr *shape, float bound_1, float bound_2)
{
    pd_count shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    pd_tensor *new_tensor = pd_tens_init_ctr(a_shape, shape_len);
    
    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    while (len-- > 0) *val++ = pd_math_rand(bound_1, bound_2);
    return new_tensor;
}

pd_tensor *pd_tens_init_cpy(pd_tensor *tensor_src)
{
    pd_count shape_len = tensor_src->shape_len;
    size_t *a_shape;
    PD_PROT_MALLOC(a_shape = pd_malloc(sizeof(size_t) * shape_len));
    size_t *tmp_a_shape = a_shape;
    size_t *shape_src = tensor_src->shape;
    for (pd_count i = 0; i < shape_len; ++i) *tmp_a_shape++ = *shape_src++;

    pd_tensor *new_tensor = pd_tens_init_ctr(a_shape, shape_len);
    
    size_t len = new_tensor->len;
    float *val = new_tensor->val;
    float *val_src = tensor_src->val;
    while (len-- > 0) *val++ = *val_src++;
    return new_tensor;
}
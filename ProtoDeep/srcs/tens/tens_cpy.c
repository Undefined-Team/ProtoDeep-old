#include "pd_main.h"

pd_tensor *pd_tens_cpy(pd_tensor *tensor_src)
{
    pd_count shape_len = tensor_src->shape_len;
    if (shape_len == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t len = tensor_src->len;

    size_t *shape;
    PD_PROT_MALLOC(shape = pd_malloc(sizeof(size_t) * shape_len));
    size_t *tmp_shape = shape;
    size_t *shape_src = tensor_src->shape;
    for (pd_count i = 0; i < shape_len; ++i)
    {
        if (*shape_src == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
        *tmp_shape++ = *shape_src++;
    }
    size_t *shape_m;
    PD_PROT_MALLOC(shape_m = pd_malloc(sizeof(size_t) * shape_len));
    size_t *tmp_shape_m = shape_m;
    size_t *shape_m_src = tensor_src->shape_m;
    for (pd_count i = 0; i < shape_len; ++i) *tmp_shape_m++ = *shape_m_src++;
    
    float *val;
    PD_PROT_MALLOC(val = pd_malloc(sizeof(float) * len));
    pd_tensor *new_tensor = pd_tens_new(val, len, shape, shape_m, shape_len);

    new_tensor->val = val;
    float *val_src = tensor_src->val;
    while (len-- > 0) *val++ = *val_src++;
    return new_tensor;
}
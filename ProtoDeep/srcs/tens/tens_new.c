#include "pd_main.h"

pd_tensor *pd_tens_new(float *val, size_t len, size_t *shape, size_t *shape_m, size_t shape_len)
{
    pd_tensor *new_tensor;
    PD_PROT_MALLOC(new_tensor = pd_malloc(sizeof(pd_tensor)));
    new_tensor->val = val;
    new_tensor->len = len;
    new_tensor->shape = shape;
    new_tensor->shape_m = shape_m;
    new_tensor->shape_len = shape_len;
    return new_tensor;
}
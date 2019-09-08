#include "pd_main.h"

pd_tensor       *pd_tens_new(size_t rank, size_t len, void *val, pd_arr shape)
{
    pd_tensor *new_tensor;

    PD_PROT_MALLOC(new_tensor = pd_malloc(sizeof(pd_tensor)));
    new_tensor->rank = rank;
    new_tensor->len = len;
    new_tensor->val = val;
    new_tensor->shape = shape;
    return new_tensor;
}
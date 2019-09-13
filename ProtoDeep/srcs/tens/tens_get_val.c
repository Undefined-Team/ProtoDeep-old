#include "pd_main.h"

float pd_tens_get_mval(pd_tensor *tensor, ...)
{
    va_list arg;
    va_start(arg, tensor);
    size_t *shape_mult = tensor->shape_m;
    pd_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (pd_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * (size_t)va_arg(arg, unsigned int);
    return *val;
}

float *pd_tens_get_mpval(pd_tensor *tensor, ...)
{
    va_list arg;
    va_start(arg, tensor);
    size_t *shape_mult = tensor->shape_m;
    pd_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (pd_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * (size_t)va_arg(arg, unsigned int);
    return val;
}

float pd_tens_get_val(pd_tensor *tensor, size_t *coord)
{
    size_t *shape_mult = tensor->shape_m;
    pd_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (pd_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * *coord++;
    return *val;
}

float *pd_tens_get_pval(pd_tensor *tensor, size_t *coord)
{
    size_t *shape_mult = tensor->shape_m;
    pd_count shape_len = tensor->shape_len;
    float *val = tensor->val;
    for (pd_count i = 0; i < shape_len; ++i)
        val += *shape_mult++ * *coord++;
    return val;
}
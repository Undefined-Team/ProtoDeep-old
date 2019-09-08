#include "pd_main.h"
// a opti

void            pd_tens_add_check_size(pd_tensor *a, pd_tensor *b)
{
    size_t min = a->shape.len > b->shape.len ? b->shape.len : a->shape.len;
    size_t matching = 0;

    size_t *a_shape_val = (size_t *)a->shape.val;
    size_t *b_shape_val = (size_t *)b->shape.val;
    for (size_t i = 0; i < min; i++)
        if (a_shape_val[i] == b_shape_val[i])
            matching++;
    if (!matching)
        pd_error("Can't add tensors with shapes %s and %s", (char *)pd_arr_get_shape(a->shape).val, (char *)pd_arr_get_shape(b->shape).val);
}

pd_tensor       *pd_tens_add(pd_tensor *a, pd_tensor *b)
{
    pd_tensor *flatten_a = pd_tens_flatten(a);
    pd_tensor *flatten_b = pd_tens_flatten(b);

    pd_tens_add_check_size(a, b);

    float *t_flatten_a_val = (float *)flatten_a->val;
    float *t_flatten_b_val = (float *)flatten_b->val;

    for (size_t i = 0; i < flatten_a->len; i++)
        t_flatten_a_val[i] = t_flatten_b_val[i % flatten_b->len];
    pd_tensor reshape = pd_tens_reshape(flatten_a, pd_arr_copy(a->shape));
    pd_tens_free(flatten_a);
    pd_tens_free(flatten_b);
    return (reshape);
}
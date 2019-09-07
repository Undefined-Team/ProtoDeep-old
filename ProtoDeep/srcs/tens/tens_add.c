#include "pd_main.h"
// a opti
pd_tensor       pd_tens_add(pd_tensor a, pd_tensor b)
{
    pd_tensor flatten_a = pd_tens_flatten(a);
    pd_tensor flatten_b = pd_tens_flatten(b);

    for (size_t i = 0; i < flatten_a.len; i++)
        ((float *)flatten_a.val)[i] = ((float *)flatten_b.val)[i % flatten_b.len];
    pd_tensor reshape = pd_tens_reshape(flatten_a, pd_arr_copy(a.shape));
    pd_tens_free(flatten_a);
    pd_tens_free(flatten_b);
    return (reshape);
}
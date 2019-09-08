#include "pd_main.h"

pd_size_t_a   pd_tens_get_shape(pd_tensor *tensor)
{
    pd_size_t_a new_shape;

    pd_free(tensor->shape.val);
    new_shape = pd_arr_init(PD_T_SIZE_T, tensor->rank);
    size_t *a_new_shape = (size_t*)new_shape.val;
    for (size_t i = 0; i < new_shape.len; i++)
    {
        a_new_shape[i] = tensor->len;
        if (tensor->rank != 1 && tensor->len != 0)
            tensor = ((pd_tensor**)tensor->val)[0];
    }
    return new_shape;
}
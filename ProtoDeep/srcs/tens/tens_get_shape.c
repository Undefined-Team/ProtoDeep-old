#include "pd_main.h"

pd_size_t_a   pd_tens_get_shape(pd_tensor tensor)
{
    pd_size_t_a new_shape;

    new_shape = pd_arrInit(PD_T_SIZE_T, tensor.rank);
    for (size_t i = 0; i < new_shape.len; i++)
    {
        ((size_t*)new_shape.val)[i] = tensor.len;
        if (tensor.rank != 1 && tensor.len != 0)
            tensor = ((pd_tensor*)tensor.val)[0];
    }
    //pd_dast_free((void**)&tensor.shape.val);
    return new_shape;
}
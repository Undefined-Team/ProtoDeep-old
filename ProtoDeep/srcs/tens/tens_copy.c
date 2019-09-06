#include "pd_main.h"

pd_tensor pd_tens_copy(pd_tensor tensor)
{
    pd_tensor new_tensor;

    new_tensor = pd_tens_new(tensor.rank, tensor.len, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
    if (new_tensor.rank == 1)
    {
        new_tensor.val = pd_malloc(sizeof(float) * new_tensor.len);
        for (size_t i = 0; i < new_tensor.len; i++)
            ((float*)new_tensor.val)[i] = ((float*)tensor.val)[i];
    }
    else
    {
        new_tensor.val = pd_malloc(sizeof(pd_tensor) * new_tensor.len);
        for (size_t i = 0; i < new_tensor.len; i++)
            ((pd_tensor*)new_tensor.val)[i] = pd_tens_copy(((pd_tensor*)tensor.val)[i]);
    }
    new_tensor.shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}
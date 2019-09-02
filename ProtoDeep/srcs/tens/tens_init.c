#include "pd_main.h"

pd_tensor   pd_tens_init(size_t *shape, size_t len)
{
    pd_tensor new_tensor;

    new_tensor.rank = len;
    new_tensor.val = NULL;
    if (new_tensor.rank == 0)
    {
        new_tensor.len = 0;
        return new_tensor;
    }
    new_tensor.len = *shape;
    if (new_tensor.rank == 1)
    {
        new_tensor.val = malloc(sizeof(float) * new_tensor.len);
        for (size_t i = 0; i < new_tensor.len; i++)
            ((float*)new_tensor.val)[i] = 0;
        return new_tensor;
    }
    new_tensor.val = malloc(sizeof(pd_tensor) * new_tensor.len);
    for (size_t i = 0; i < new_tensor.len; i++)
        ((pd_tensor*)new_tensor.val)[i] = pd_tens_init(shape++, len - 1);
    return new_tensor;
}

pd_size_t   pd_tens_get_shape(pd_tensor tensor)
{
    pd_size_t new_shape;

    new_shape = arrInit(PD_T_SIZE_T, tensor.rank);
    for (size_t i = 0; i < tensor.rank; i++)
    {
        ((size_t)new_shape.val)[i] = tensor.len;
        tensor = ((pd_tensor*)tensor.val)[0];
    }
    return new_shape;
}
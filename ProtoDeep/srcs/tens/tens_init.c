#include "pd_main.h"

pd_tensor   pd_tens_init(size_t *shape, size_t rank)
{
    pd_tensor new_tensor;

    new_tensor.rank = rank;
    new_tensor.val = NULL;
    new_tensor.shape.val = NULL;
    if (new_tensor.rank == 0)
        pd_error("Rank must be greater than 0 (Bad shape <-> len ?)");
    else if (shape == NULL)
        pd_error("A shape value is null (Bad shape <-> len ?)");
    if (*shape == 0)
    {
        new_tensor.len = 0;
        new_tensor.shape = pd_tens_get_shape(new_tensor);
        return new_tensor;
    }
    new_tensor.len = *shape;
    if (new_tensor.rank == 1)
    {
        new_tensor.val = pd_malloc(sizeof(float) * new_tensor.len);
        for (size_t i = 0; i < new_tensor.len; i++)
            ((float*)new_tensor.val)[i] = 0;
        new_tensor.shape = pd_tens_get_shape(new_tensor);
        return new_tensor;
    }
    new_tensor.val = pd_malloc(sizeof(pd_tensor) * new_tensor.len);
    for (size_t i = 0; i < new_tensor.len; i++)
        ((pd_tensor*)new_tensor.val)[i] = pd_tens_init(&shape[1], rank - 1);
    new_tensor.shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}
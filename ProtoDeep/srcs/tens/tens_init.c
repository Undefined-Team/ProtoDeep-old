#include "pd_main.h"

pd_tensor   pd_tens_init_ctr(size_t *shape, size_t rank)
{
    pd_tensor new_tensor;

    new_tensor = pd_tens_new(rank, 0, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
    if (new_tensor.rank == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    else if (shape == NULL) pd_error("A shape value is null (Bad shape <-> length ?)");
    else if (*shape == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
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
        ((pd_tensor*)new_tensor.val)[i] = pd_tens_init_ctr(&shape[1], rank - 1);
    new_tensor.shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}

pd_tensor   pd_tens_init_rand_ctr(size_t *shape, size_t rank, float bound_a, float bound_b)
{
    pd_tensor new_tensor;

    new_tensor = pd_tens_new(rank, 0, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
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
            ((float*)new_tensor.val)[i] = pd_math_rand(bound_a, bound_b);
        new_tensor.shape = pd_tens_get_shape(new_tensor);
        return new_tensor;
    }
    new_tensor.val = pd_malloc(sizeof(pd_tensor) * new_tensor.len);
    for (size_t i = 0; i < new_tensor.len; i++)
        ((pd_tensor*)new_tensor.val)[i] = pd_tens_init_rand_ctr(&shape[1], rank - 1, bound_a, bound_b);
    new_tensor.shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}

pd_tensor   pd_tens_init(pd_size_t_a shape)
{
    return pd_tens_init_ctr((size_t*)shape.val, shape.len);
}

pd_tensor   pd_tens_init_rand(pd_size_t_a shape, float bound_a, float bound_b)
{
    return pd_tens_init_rand_ctr((size_t*)shape.val, shape.len, bound_a, bound_b);
}

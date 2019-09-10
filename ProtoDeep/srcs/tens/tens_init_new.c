#include "pd_main.h"

static size_t *pd_get_shape_div(size_t *a_shape, size_t shape_len, size_t *nbr_float, size_t *nbr_p_tensor)
{
    size_t *a_shape_div = malloc(sizeof(size_t) * shape_len);
    size_t t_nbr_p_tensor = a_shape[0];
    size_t shape_mult = t_nbr_p_tensor;
    a_shape_div[0] = 1;
    size_t i = 0;
    while (++i < shape_len - 1)
    {
        a_shape_div[i] = shape_mult + a_shape_div[i - 1];
        shape_mult *= a_shape[i];
        t_nbr_p_tensor += shape_mult;
    }
    a_shape_div[i] = shape_mult + a_shape_div[i - 1];
    shape_mult *= a_shape[i];
    *nbr_float = shape_mult;
    *nbr_p_tensor = t_nbr_p_tensor;
    return a_shape_div;
}

pd_tensor   *pd_tens_init_new(pd_size_t_a *shape)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    size_t shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    size_t *shape_div = pd_get_shape_div(a_shape, shape_len, &nbr_float, &nbr_p_tensor);
    nbr_tensor = nbr_p_tensor + 1;

    float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len);
    pd_mem_set(mem_float, 0, sizeof(float) * nbr_float);

    size_t i = 0;
    size_t j = 0;
    size_t i_p_tensor = 0;
    size_t i_tensor = 1;
    size_t step;
    size_t rank = shape_len;
    size_t t_shape;
    size_t t_shape_div;
    pd_size_t_a *new_shape;
    while (i < shape_len - 1)
    {
        new_shape = &new_shapes[i];
        pd_arr_val(new_shape, PD_T_SIZE_T, rank, &a_shape[i]);
        t_shape_div = shape_div[i];
        t_shape = a_shape[i];
        while (j < t_shape_div)
        {
            mem_tensor[j].val = &mem_p_tensor[i_p_tensor];
            step = t_shape;
            mem_tensor[j].len = step;
            mem_tensor[j].rank = rank;
            mem_tensor[j].shape = new_shape;
            for (size_t k = 0; k < step; k++)
                mem_p_tensor[i_p_tensor++] = &mem_tensor[i_tensor++];
            j++;
        }
        rank--;
        i++;
    }

    size_t i_float = 0;
    step = a_shape[i];
    new_shape = &new_shapes[i];
    pd_arr_val(new_shape, PD_T_SIZE_T, 1, &a_shape[i]);
    t_shape_div = shape_div[i];
    while (j < t_shape_div)
    {
        mem_tensor[j].val = &mem_float[i_float];
        mem_tensor[j].len = step;
        mem_tensor[j].rank = 1;
        mem_tensor[j].shape = new_shape;
        i_float += step;
        j++;
    }
    pd_free(shape_div);
    return &mem_tensor[0];
}
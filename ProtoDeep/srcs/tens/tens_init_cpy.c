#include "pd_main.h"

pd_tensor *pd_tens_init_cpy(pd_tensor *tens_src)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    pd_size_t_a *shape = pd_arr_copy(tens_src->shape);
    pd_count shape_len = shape->len;
    if (shape_len == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    size_t *shape_div = pd_get_shape_div(a_shape, shape_len, &nbr_float, &nbr_p_tensor, &nbr_tensor);

    float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len); 

    while (tens_src->rank > 1) tens_src = ((pd_tensor**)tens_src->val)[0];

    pd_s_mem_tensor s_mem_tensor =
    {
        .shape_len = shape_len,
        .new_shapes = new_shapes,
        .a_shape = a_shape,
        .shape_div = shape_div,
        .mem_tensor = mem_tensor,
        .mem_p_tensor = mem_p_tensor,
    };
    pd_s_mem_float s_mem_float =
    {
        .shape_len = shape_len,
        .new_shapes = new_shapes,
        .a_shape = a_shape,
        .shape_div = shape_div,
        .mem_tensor = mem_tensor,
        .mem_float = mem_float,
        .init_type = PD_TENS_INIT_CPY,
        .init_src = (float*)tens_src->val,
    };
    pd_tensor *ret = pd_tens_init_ctr(&s_mem_tensor, &s_mem_float);
    pd_free(shape_div);
    return ret;
}
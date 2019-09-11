#include "pd_main.h"

pd_tensor *pd_tens_init(pd_size_t_a *shape)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    size_t shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    size_t *shape_div = pd_get_shape_div(a_shape, shape_len, &nbr_float, &nbr_p_tensor, &nbr_tensor);

    float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len); 
    
    pd_s_mem_tensor     s_mem_tensor    = pd_get_mem_tensor(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_p_tensor);
    pd_s_mem_p_tensor   s_mem_p_tensor  = pd_get_mem_p_tensor(nbr_p_tensor, mem_tensor, mem_p_tensor);
    pd_s_mem_float      s_mem_float     = pd_get_mem_float(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_float);
    pd_tensor *ret = pd_tens_init_ctr(s_mem_tensor, s_mem_p_tensor, s_mem_float);
    pd_free(shape_div);
    return ret;
}
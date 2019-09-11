#include "pd_main.h"

typedef struct          pds_s_val_init_rand {
    float               *mem_float;
    size_t              i;
    size_t              len;
    float               bound_a;
    float               bound_b;
}                       pd_s_val_init_rand;

pd_s_val_init_rand pd_val_init_rand(float *mem_float, size_t i, size_t len, float bound_a, float bound_b)
{
    pd_s_val_init_rand new_s;
    new_s.mem_float = mem_float;
    new_s.i         = i;
    new_s.len       = len;
    new_s.bound_a   = bound_a;
    new_s.bound_b   = bound_b;
    return new_s;
}

static void        *pd_apply_init_rand(void *p_data)
{
    pd_s_val_init_rand  *st         = (pd_s_val_init_rand*)p_data;
    float               *mem_float  = st->mem_float;
    size_t              i           = st->i;
    size_t              len         = st->len;
    float               bound_a     = st->bound_a;
    float               bound_b     = st->bound_b;

    for (;i < len; i++) mem_float[i] = pd_math_rand(bound_a, bound_b);
    pthread_exit(NULL);
}

pd_tensor *pd_tens_init_rand(pd_size_t_a *shape, float bound_a, float bound_b)
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

    size_t thread_nbr = 3;
    if (thread_nbr > 1)
    {
        pthread_t threads[thread_nbr];
        pd_s_val_init_rand init_rand[thread_nbr];
        size_t divide = nbr_float / thread_nbr;
        size_t div_tmp = 0;
        size_t i = 0;
        while (i < thread_nbr - 1)
        {
            init_rand[i] = pd_val_init_rand(mem_float, div_tmp, div_tmp + divide, bound_a, bound_b);
            div_tmp += divide;
            pthread_create(&threads[i], NULL, pd_apply_init_rand, &init_rand[i]);
            i++;
        }
        init_rand[i] = pd_val_init_rand(mem_float, div_tmp, nbr_float, bound_a, bound_b);
        pthread_create(&threads[i], NULL, pd_apply_init_rand, &init_rand[i]);
        for(size_t i = 0; i < thread_nbr; i++) pthread_join(threads[i], NULL);
    }
    else
        for (size_t i = 0; i < nbr_float; i++) mem_float[i] = pd_math_rand(bound_a, bound_b);
    
    pd_s_mem_tensor     s_mem_tensor    = pd_get_mem_tensor(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_p_tensor);
    pd_s_mem_p_tensor   s_mem_p_tensor  = pd_get_mem_p_tensor(nbr_p_tensor, mem_tensor, mem_p_tensor);
    pd_s_mem_float      s_mem_float     = pd_get_mem_float(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_float);
    pd_tensor *ret = pd_tens_init_ctr(s_mem_tensor, s_mem_p_tensor, s_mem_float);
    pd_free(shape_div);
    return ret;
}
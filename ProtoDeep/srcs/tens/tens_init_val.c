#include "pd_main.h"

typedef struct          pds_s_val_init_val {
    float               *mem_float;
    size_t              i;
    size_t              len;
    float               val;
}                       pd_s_val_init_val;

pd_s_val_init_val pd_val_init_val(float *mem_float, size_t i, size_t len, float val)
{
    pd_s_val_init_val new_s;
    new_s.mem_float = mem_float;
    new_s.i         = i;
    new_s.len       = len;
    new_s.val       = val;
    return new_s;
}

static void        *pd_apply_init_val(void *p_data)
{
    pd_s_val_init_val   *st         = (pd_s_val_init_val*)p_data;
    float               *mem_float  = st->mem_float;
    size_t              i           = st->i;
    size_t              len         = st->len;
    float               val         = st->val;

    for (;i < len; i++) mem_float[i] = val;
    pthread_exit(NULL);
}

pd_tensor *pd_tens_init_val(pd_size_t_a *shape, float val)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    size_t shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    size_t *shape_div = pd_get_shape_div(a_shape, shape_len, &nbr_float, &nbr_p_tensor, &nbr_tensor);
    // printf("%zd %zd %zd\n", nbr_float, nbr_p_tensor, nbr_tensor);

    float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len); 

    size_t thread_nbr = 3;
    if (thread_nbr > 1)
    {
        pthread_t threads[thread_nbr];
        pd_s_val_init_val init_val[thread_nbr];
        size_t divide = nbr_float / thread_nbr;
        size_t div_tmp = 0;
        size_t i = 0;
        while (i < thread_nbr - 1)
        {
            init_val[i] = pd_val_init_val(mem_float, div_tmp, div_tmp + divide, val);
            div_tmp += divide;
            pthread_create(&threads[i], NULL, pd_apply_init_val, &init_val[i]);
            i++;
        }
        init_val[i] = pd_val_init_val(mem_float, div_tmp, nbr_float, val);
        pthread_create(&threads[i], NULL, pd_apply_init_val, &init_val[i]);
        for(size_t i = 0; i < thread_nbr; i++) pthread_join(threads[i], NULL);
    }
    else
        for (size_t i = 0; i < nbr_float; i++) mem_float[i] = val;
    
    pd_s_mem_tensor     s_mem_tensor    = pd_get_mem_tensor(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_p_tensor);
    pd_s_mem_p_tensor   s_mem_p_tensor  = pd_get_mem_p_tensor(nbr_p_tensor, mem_tensor, mem_p_tensor);
    pd_s_mem_float      s_mem_float     = pd_get_mem_float(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_float);
    pd_tensor *ret = pd_tens_init_ctr(s_mem_tensor, s_mem_p_tensor, s_mem_float);
    pd_free(shape_div);
    return ret;
}
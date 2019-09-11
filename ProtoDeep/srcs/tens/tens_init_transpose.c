#include "pd_main.h"

/*typedef struct          pds_s_val_init_cpy {
    float               *mem_float;
    size_t              i;
    size_t              len;
    pd_tensor           *tens_src;
}                       pd_s_val_init_cpy;

pd_s_val_init_cpy pd_val_init_cpy(float *mem_float, size_t i, size_t len, pd_tensor *tens_src)
{
    pd_s_val_init_cpy new_s;
    new_s.mem_float = mem_float;
    new_s.i         = i;
    new_s.len       = len;
    new_s.tens_src  = tens_src;
    return new_s;
}

static void        *pd_apply_init_cpy(void *p_data)
{
    pd_s_val_init_cpy   *st         = (pd_s_val_init_cpy*)p_data;
    float               *mem_float  = st->mem_float;
    size_t              i           = st->i;
    size_t              len         = st->len;
    pd_tensor           *tens_src   = st->tens_src;

    float *cpy_src;
    while (tens_src->rank > 1) tens_src = ((pd_tensor**)tens_src->val)[0];
    cpy_src = (float*)tens_src->val;
    for (;i < len; i++) mem_float[i] = cpy_src[i];
    pthread_exit(NULL);
}*/
static pd_size_t_a     *pd_get_new_shape(pd_size_t_a *shape, pd_size_t_a *new_dim)
{
    size_t shape_len = shape->len;
    pd_size_t_a *new_shape = pd_arr_init(PD_T_SIZE_T, shape_len);
    size_t *a_new_shape = (size_t*)new_shape->val;
    size_t *a_shape = (size_t*)shape->val;
    size_t *a_new_dim = (size_t*)new_dim->val;
    size_t t_shape_val;
    for (size_t i = 0; i < shape_len; i++)
    {
        t_shape_val = a_shape[a_new_dim[i]];
        a_new_shape[i] = t_shape_val;
    }
    return new_shape;
}

void pd_tens_init_transpose(pd_tensor *tens_src, pd_size_t_a *new_dim)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    pd_size_t_a *shape = pd_arr_copy(tens_src->shape);
    size_t shape_len = shape->len;
    size_t *a_shape = (size_t*)shape->val;
    pd_free(shape);

    pd_size_t_a *new_shape = pd_get_new_shape(tens_src->shape, new_dim);
    size_t *a_new_shape = (size_t*)new_shape->val;
    size_t *shape_div = pd_get_shape_div(a_new_shape, shape_len, &nbr_float, &nbr_p_tensor, &nbr_tensor);

    pd_tensor *tmp_tensor       = tens_src;
    while (tmp_tensor->rank > 1) tmp_tensor = ((pd_tensor**)tmp_tensor->val)[0];
    float     *mem_float        = (float*)tmp_tensor->val;
    pd_tensor *mem_tensor       = tens_src;
    pd_tensor **mem_p_tensor    = (pd_tensor**)tens_src->val;
    pd_arr    *new_shapes       = tens_src->shape;
    /*float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len); 

    size_t thread_nbr = 3;
    if (thread_nbr > 1)
    {
        pthread_t threads[thread_nbr];
        pd_s_val_init_cpy init_cpy[thread_nbr];
        size_t divide = nbr_float / thread_nbr;
        size_t div_tmp = 0;
        size_t i = 0;
        while (i < thread_nbr - 1)
        {
            init_cpy[i] = pd_val_init_cpy(mem_float, div_tmp, div_tmp + divide, tens_src);
            div_tmp += divide;
            pthread_create(&threads[i], NULL, pd_apply_init_cpy, &init_cpy[i]);
            i++;
        }
        init_cpy[i] = pd_val_init_cpy(mem_float, div_tmp, nbr_float, tens_src);
        pthread_create(&threads[i], NULL, pd_apply_init_cpy, &init_cpy[i]);
        for(size_t i = 0; i < thread_nbr; i++) pthread_join(threads[i], NULL);
    }
    else
    {
        float *cpy_src;
        while (tens_src->rank > 1) tens_src = ((pd_tensor**)tens_src->val)[0];
        cpy_src = (float*)tens_src->val;
        for (size_t i = 0; i < nbr_float; i++) mem_float[i] = cpy_src[i];
    }*/
    
    pd_s_mem_tensor     s_mem_tensor    = pd_get_mem_tensor(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_p_tensor);
    pd_s_mem_p_tensor   s_mem_p_tensor  = pd_get_mem_p_tensor(nbr_p_tensor, mem_tensor, mem_p_tensor);
    pd_s_mem_float      s_mem_float     = pd_get_mem_float(shape_len, new_shapes, a_shape, shape_div, mem_tensor, mem_float);
    pd_tensor *ret = pd_tens_init_ctr(s_mem_tensor, s_mem_p_tensor, s_mem_float);
    pd_free(shape_div);
    //return ret;
    (void)ret;
}
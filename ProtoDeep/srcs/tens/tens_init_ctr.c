#include "pd_main.h"

size_t *pd_get_shape_div(size_t *a_shape, pd_count shape_len, size_t *nbr_float, size_t *nbr_p_tensor, size_t *nbr_tensor)
{
    if (a_shape[0] == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
    size_t *a_shape_div = malloc(sizeof(size_t) * shape_len);
    if (shape_len == 1)
    {
        *nbr_float = a_shape[0];
        *nbr_tensor = 1;
        *nbr_p_tensor = 0;
        a_shape_div[0] = 1;
        return a_shape_div;
    }
    pd_count t_nbr_p_tensor = a_shape[0];
    pd_count shape_mult = t_nbr_p_tensor;
    a_shape_div[0] = 1;
    pd_count i = 0;
    pd_count len = shape_len - 1;
    while (++i < len)
    {
        if (a_shape[i] == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
        a_shape_div[i] = shape_mult + a_shape_div[i - 1];
        shape_mult *= a_shape[i];
        t_nbr_p_tensor += shape_mult;
    }
    if (a_shape[i] == 0) pd_error("Shape can't have a dimension of length 0 (Bad shape)");
    a_shape_div[i] = shape_len > 1 ? shape_mult + a_shape_div[i - 1] : 1;
    shape_mult *= a_shape[i];
    *nbr_float = shape_mult;
    *nbr_p_tensor = t_nbr_p_tensor;
    *nbr_tensor = t_nbr_p_tensor + 1;
    return a_shape_div;
}

/*static void *pd_set_mem_tensor(void * p_data)
{
    pd_s_mem_tensor *st         = (pd_s_mem_tensor*)p_data;
    pd_count    shape_len       = st->shape_len;
    pd_arr      *new_shapes     = st->new_shapes;
    size_t      *a_shape        = st->a_shape;
    size_t      *shape_div      = st->shape_div;
    pd_tensor   *mem_tensor     = st->mem_tensor;
    pd_tensor   **mem_p_tensor  = st->mem_p_tensor;

    pd_count i = 0;
    pd_count j = 0;
    pd_count i_p_tensor = 0;
    pd_count i_tensor = 1;
    pd_count step;
    pd_count rank = shape_len;
    pd_count t_shape;
    pd_count t_shape_div;
    pd_count k;
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
            for (k = 0; k < step; ++k)
            {
                mem_p_tensor[i_p_tensor] = &mem_tensor[i_tensor];
                ++i_p_tensor;
                ++i_tensor;
            }
            ++j;
        }
        --rank;
        ++i;
    }
    pthread_exit(NULL);
}*/

static void *pd_set_mem_tensor(void * p_data)
{
// struct timespec start, finish;
// double elapsed;
// clock_gettime(CLOCK_MONOTONIC, &start);

    pd_s_mem_tensor *st         = (pd_s_mem_tensor*)p_data;
    pd_count    shape_len       = st->shape_len;
    pd_arr      *new_shapes     = st->new_shapes;
    size_t      *a_shape        = st->a_shape;
    size_t      *shape_div      = st->shape_div;
    pd_tensor   *mem_tensor     = st->mem_tensor;
    pd_tensor   *mem_tensor_2   = mem_tensor + 1;
    pd_tensor   **mem_p_tensor  = st->mem_p_tensor;

    pd_count i = 0;
    pd_count j = 0;
    pd_count i_p_tensor = 0;
    pd_count i_tensor = 1;
    pd_count step;
    pd_count rank = shape_len;
    pd_count t_shape;
    pd_count t_shape_div;
    pd_count k;
    pd_size_t_a *new_shape;

    // pd_tensor *mem_tensor_limit;
    --shape_len;
    while (i < shape_len)
    {
        new_shape = &new_shapes[i];
        pd_arr_val(new_shape, PD_T_SIZE_T, rank, &a_shape[i]);
        t_shape_div = shape_div[i];
        t_shape = a_shape[i];
        while (j < t_shape_div)
        {
            mem_tensor->val = mem_p_tensor;
            step = t_shape;
            mem_tensor->len = step;
            mem_tensor->rank = rank;
            mem_tensor->shape = new_shape;
            for (k = 0; k < step; ++k)
            {
                *mem_p_tensor = mem_tensor_2;
                ++mem_p_tensor;
                ++mem_tensor_2;
            }
            ++mem_tensor;
            ++j;
        }
        --rank;
        ++i;
    }
//     clock_gettime(CLOCK_MONOTONIC, &finish);
// elapsed = (finish.tv_sec - start.tv_sec);
// elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// printf("set float take %lf\n", elapsed);
//     pthread_exit(NULL);
}
/*
static void *pd_set_mem_float(void * p_data)
{
    pd_s_mem_float      *st             = (pd_s_mem_float*)p_data;
    size_t              shape_len       = st->shape_len;
    pd_arr              *new_shapes     = st->new_shapes;
    size_t              *a_shape        = st->a_shape;
    size_t              *shape_div      = st->shape_div;
    pd_tensor           *mem_tensor     = st->mem_tensor;
    float               *mem_float      = st->mem_float;
    pd_tens_init_type   init_type       = st->init_type;

    pd_count i = shape_len - 1;
    pd_count j = shape_len > 1 ? shape_div[i]  - (shape_div[i] -  shape_div[i - 1]) : 0;
    pd_count i_float = 0;
    pd_count step = a_shape[i];
    pd_arr *new_shape = &new_shapes[i];
    pd_arr_val(new_shape, PD_T_SIZE_T, 1, &a_shape[i]);
    size_t t_shape_div = shape_div[i];
    if (init_type == PD_TENS_INIT)
    {
        while (j < t_shape_div)
        {
            mem_tensor[j].val = &mem_float[i_float];
            mem_tensor[j].len = step;
            mem_tensor[j].rank = 1;
            mem_tensor[j].shape = new_shape;
            i_float += step;
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_VAL)
    {
        float val = *(float*)st->init_src;
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor[j].val = &mem_float[i_float];
            mem_tensor[j].len = step;
            mem_tensor[j].rank = 1;
            mem_tensor[j].shape = new_shape;
            for (k = 0; k < step; ++k)
            {
                mem_float[i_float] = val;
                ++i_float;
            }
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_RAND)
    {
        float *val = (float*)st->init_src;
        float bound_1 = val[0];
        float bound_2 = val[1];
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor[j].val = &mem_float[i_float];
            mem_tensor[j].len = step;
            mem_tensor[j].rank = 1;
            mem_tensor[j].shape = new_shape;
            for (k = 0; k < step; ++k)
            {
                mem_float[i_float] = pd_math_rand(bound_1, bound_2);
                ++i_float;
            }
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_CPY)
    {
        float *val = (float*)st->init_src;
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor[j].val = &mem_float[i_float];
            mem_tensor[j].len = step;
            mem_tensor[j].rank = 1;
            mem_tensor[j].shape = new_shape;
            for (k = 0; k < step; ++k)
            {
                mem_float[i_float] = val[i_float];
                ++i_float;
            }
            ++j;
        }
    }
    pthread_exit(NULL);
}*/


static void *pd_set_mem_float(void * p_data)
{
// struct timespec start, finish;
// double elapsed;
// clock_gettime(CLOCK_MONOTONIC, &start);

    pd_s_mem_float      *st             = (pd_s_mem_float*)p_data;
    size_t              shape_len       = st->shape_len;
    pd_arr              *new_shapes     = st->new_shapes;
    size_t              *a_shape        = st->a_shape;
    size_t              *shape_div      = st->shape_div;
    pd_tensor           *mem_tensor     = st->mem_tensor;
    float               *mem_float      = st->mem_float;
    pd_tens_init_type   init_type       = st->init_type;

    pd_count i = shape_len - 1;
    pd_count j = shape_len > 1 ? shape_div[i]  - (shape_div[i] -  shape_div[i - 1]) : 0;
    // pd_tensor           *mem_tensor     =  shape_len > 1 ? st->mem_tensor + (shape_div[i]  - (shape_div[i] -  shape_div[i - 1])) : st->mem_tensor;
    mem_tensor += j;

    pd_count i_float = 0;
    pd_count step = a_shape[i];
    pd_arr *new_shape = &new_shapes[i];
    pd_arr_val(new_shape, PD_T_SIZE_T, 1, &a_shape[i]);
    size_t t_shape_div = shape_div[i];
    if (init_type == PD_TENS_INIT)
    {
        while (j < t_shape_div)
        {
            mem_tensor->val = mem_float;
            mem_tensor->len = step;
            mem_tensor->rank = 1;
            mem_tensor->shape = new_shape;
            mem_float += step;
            ++mem_tensor;
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_VAL)
    {
        float val = *(float*)st->init_src;
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor->val = mem_float;
            mem_tensor->len = step;
            mem_tensor->rank = 1;
            mem_tensor->shape = new_shape;
            for (k = 0; k < step; ++k)
                *mem_float++ = val;
            ++mem_tensor;
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_RAND)
    {
        float *val = (float*)st->init_src;
        float bound_1 = val[0];
        float bound_2 = val[1];
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor->val = mem_float;
            mem_tensor->len = step;
            mem_tensor->rank = 1;
            mem_tensor->shape = new_shape;
            for (k = 0; k < step; ++k)
                *mem_float++ = pd_math_rand(bound_1, bound_2);
            ++mem_tensor;
            ++j;
        }
    }
    else if (init_type == PD_TENS_INIT_CPY)
    {
        float *val = (float*)st->init_src;
        pd_count k;
        while (j < t_shape_div)
        {
            mem_tensor->val = mem_float;
            mem_tensor->len = step;
            mem_tensor->rank = 1;
            mem_tensor->shape = new_shape;
            for (k = 0; k < step; ++k)
                *mem_float++ = *val++;
            ++mem_tensor;
            ++j;
        }
    }

// clock_gettime(CLOCK_MONOTONIC, &finish);
// elapsed = (finish.tv_sec - start.tv_sec);
// elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
// printf("set tensor take %lf\n", elapsed);
    pthread_exit(NULL);
}

pd_tensor   *pd_tens_init_ctr(pd_s_mem_tensor *s_mem_tensor, pd_s_mem_float *s_mem_float)
{
    pthread_t thread_b[2];
    pthread_create(&thread_b[0], NULL, pd_set_mem_float, s_mem_float);
    pthread_create(&thread_b[1], NULL, pd_set_mem_tensor, s_mem_tensor);
    for(pd_count i = 0; i < 2; i++) pthread_join(thread_b[i], NULL);
    return &s_mem_tensor->mem_tensor[0];
}
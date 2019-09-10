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

typedef struct pds_s_mem_tensor {
    size_t      shape_len;
    pd_arr      *new_shapes;
    size_t      *a_shape;
    size_t      *shape_div;
    pd_tensor   *mem_tensor;
    pd_tensor   **mem_p_tensor;
}               pd_s_mem_tensor;

typedef struct pds_s_mem_p_tensor {
    size_t      nbr_p_tensor;
    pd_tensor   *mem_tensor;
    pd_tensor   **mem_p_tensor;
}               pd_s_mem_p_tensor;

typedef struct pds_s_mem_float {
    size_t      shape_len;
    pd_arr      *new_shapes;
    size_t      *a_shape;
    size_t      *shape_div;
    pd_tensor   *mem_tensor;
    float       *mem_float;
}               pd_s_mem_float;

static void *pd_set_mem_tensor(void * p_data)
{
    pd_s_mem_tensor st          = *(pd_s_mem_tensor*)p_data;
    size_t      shape_len       = st.shape_len;
    pd_arr      *new_shapes     = st.new_shapes;
    size_t      *a_shape        = st.a_shape;
    size_t      *shape_div      = st.shape_div;
    pd_tensor   *mem_tensor     = st.mem_tensor;
    pd_tensor   **mem_p_tensor  = st.mem_p_tensor;

    size_t i = 0;
    size_t j = 0;
    size_t i_p_tensor = 0;
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
            i_p_tensor += step;
            j++;
        }
        rank--;
        i++;
    }
    pthread_exit(NULL);
}

static void *pd_set_mem_p_tensor(void * p_data)
{
    pd_s_mem_p_tensor st        = *(pd_s_mem_p_tensor*)p_data;
    pd_tensor   *mem_tensor     = &st.mem_tensor[1];
    pd_tensor   **mem_p_tensor  = st.mem_p_tensor;

    size_t len = st.nbr_p_tensor;
    for (size_t i = 0; i < len; i++)
        mem_p_tensor[i] = &mem_tensor[i];
    pthread_exit(NULL);
}

static void *pd_set_mem_float(void * p_data)
{
    pd_s_mem_float st = *(pd_s_mem_float*)p_data;
    size_t      shape_len       = st.shape_len;
    pd_arr      *new_shapes     = st.new_shapes;
    size_t      *a_shape        = st.a_shape;
    size_t      *shape_div      = st.shape_div;
    pd_tensor   *mem_tensor     = st.mem_tensor;
    float       *mem_float      = st.mem_float;

    size_t j = shape_div[shape_len - 1]  - (shape_div[shape_len - 1] -  shape_div[shape_len - 2]);
    size_t i = shape_len - 1;
    size_t i_float = 0;
    size_t step = a_shape[i];
    pd_arr *new_shape = &new_shapes[i];
    pd_arr_val(new_shape, PD_T_SIZE_T, 1, &a_shape[i]);
    size_t t_shape_div = shape_div[i];
    while (j < t_shape_div)
    {
        mem_tensor[j].val = &mem_float[i_float];
        mem_tensor[j].len = step;
        mem_tensor[j].rank = 1;
        mem_tensor[j].shape = new_shape;
        i_float += step;
        j++;
    }
    pthread_exit(NULL);
}

pd_tensor   *pd_tens_init_new_new(pd_size_t_a *shape)
{
    if (shape->len == 1)
    {
        pd_tensor *tensor = malloc(sizeof(pd_tensor));
        size_t nbr_float = ((size_t *)shape->val)[0];
        
        tensor->rank = 1;
        tensor->len = nbr_float;
        tensor->val = malloc(nbr_float * sizeof(float));
        tensor->shape = shape;
        pd_mem_set(tensor->val, 0, sizeof(float) * nbr_float);
        return (tensor);
    }
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

    pd_s_mem_tensor s_mem_tensor =
    {
        .shape_len = shape_len,
        .new_shapes = new_shapes,
        .a_shape = a_shape,
        .shape_div = shape_div,
        .mem_tensor = mem_tensor,
        .mem_p_tensor = mem_p_tensor,
    };

    pd_s_mem_p_tensor s_mem_p_tensor =
    {
        .nbr_p_tensor = nbr_p_tensor,
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
    };
    pthread_t thread[3];
    pthread_create(&thread[0], NULL, pd_set_mem_tensor, &s_mem_tensor);
    pthread_create(&thread[1], NULL, pd_set_mem_p_tensor, &s_mem_p_tensor);
    pthread_create(&thread[2], NULL, pd_set_mem_float, &s_mem_float);
    for(size_t i = 0; i < 3; i++) pthread_join(thread[i], NULL);
    pd_free(shape_div);
    return &mem_tensor[0];
}
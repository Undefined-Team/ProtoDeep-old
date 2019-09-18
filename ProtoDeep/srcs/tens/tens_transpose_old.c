#include "pd_main.h"

static size_t       *pd_error_manager(pd_arr *new_dim, size_t shape_len)
{
    if (shape_len != new_dim->len) pd_error("There must be as many new dimensions as the rank of the tensor-> (tensor->rank == new_dim->len)");
    bool valid[new_dim->len];
    pd_mem_set(valid, false, sizeof(bool) * new_dim->len);
    size_t *t_new_dim = (size_t*)new_dim->val;
    size_t t_index;
    size_t new_dim_len = new_dim->len;
    for (size_t i = 0; i < new_dim_len; i++)
    {
        t_index = t_new_dim[i];
        if (t_index >= new_dim_len) pd_error("A dimension can't be greater than the number of dimensions (new_dim->val[i] < new_dim->length)");
        else if (valid[t_index] == true) pd_error("2 dimensions can't have the same dimension");
        valid[t_index] = true;
    }
    return t_new_dim;
}

static size_t       *pd_get_new_shape(size_t *shape, pd_size_t_a *new_dim)
{
    size_t shape_len = new_dim->len; // WARNING IF MAKE FEATURE OF 1 DIM GUESS
    size_t *new_shape;
    PD_PROT_MALLOC(new_shape = pd_malloc(sizeof(size_t) * shape_len));
    size_t *a_new_shape = new_shape;
    size_t *a_new_dim = (size_t*)new_dim->val;
    while (shape_len-- > 0) *a_new_shape++ = shape[*a_new_dim++];
    return new_shape;
}

static size_t       pd_get_index(size_t len, size_t *coord, size_t *new_dim, size_t *new_shape_mult)
{
    size_t index = 0;
    for (size_t i = 0; i < len; i++)
        index += coord[*new_dim++] * *new_shape_mult++;
    return index;
}

static void pd_set_shape_shapem_max(size_t *old_shape, size_t *old_shape_m, size_t *new_dim, size_t *n_shape, size_t *n_shape_m, int *n_max, size_t shape_len)
{
    int *old_n_map = n_max;
    *n_max-- = 0;
    while (shape_len-- > 1)
    {
        *n_shape   = old_shape[*new_dim];
        *n_shape_m = old_shape_m[*new_dim--];
        *n_max--   = (*n_shape-- - 1) * *n_shape_m + *old_n_map;
        *old_n_map-- = *n_shape_m-- - *old_n_map;
    }
    *n_shape   = old_shape[*new_dim];
    *n_shape_m = old_shape_m[*new_dim];
    *old_n_map = *n_shape_m - *old_n_map;
}


static void         pd_coord_update(size_t *n_shape, size_t *coord, size_t *n_shape_m, int *n_max, size_t *index)
{
    if (*coord == *n_shape)
    {
        *coord = 0;
        --coord;
        ++(*coord);
        // *index -= *n_max;
        pd_coord_update(n_shape - 1, coord, n_shape_m - 1, n_max - 1, index);
    }
    else
    {
        // *index += *n_shape_m - *n_max;
        // printf("%zd\n", *n_shape_m - *n_max);
        *index += *n_max;
    }
}

// static void         pd_coord_update_first(size_t *n_shape, size_t *coord, size_t *n_shape_m, size_t *n_max, size_t *index)
// {
//     if (*coord == *n_shape)
//     {
//         *coord = 0;
//         --coord;
//         ++(*coord);
//         // *index -= *n_max;
//         pd_coord_update(n_shape - 1, coord, n_shape_m - 1, n_max, index);
//     }
//     else
//     {
//         *index += *n_shape_m;
//     }
// }

pd_tensor       *pd_tens_transpose_cpy(pd_tensor *tensor, pd_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = pd_error_manager(new_dim, shape_len);
    size_t len = tensor->len;

    size_t b_shape[shape_len];
    size_t b_shape_m[shape_len];
    int b_max[shape_len];
    size_t *n_shape = b_shape + (shape_len - 1);
    size_t *n_shape_m = b_shape_m + (shape_len - 1);
    int *n_max = b_max + (shape_len - 1);
    size_t *n_new_dim = t_new_dim + (shape_len - 1);
    pd_set_shape_shapem_max(tensor->shape, tensor->shape_m, n_new_dim, n_shape, n_shape_m, n_max, shape_len);


    size_t coord[shape_len];
    size_t *coord_x = coord - 1;
    for (pd_count i = 0; i < shape_len; ++i) *++coord_x = 0;

    float *new_val;
    PD_PROT_MALLOC(new_val = pd_malloc(sizeof(float) * len));
    float *end_val = new_val + (len - 1);
    float *beg_val = new_val;
    float *t_beg_val = tensor->val;
    float *t_end_val = t_beg_val + len - 1;

    size_t index = 0;
    pd_count tmp_len = len / 2;
    while (tmp_len-- > 0)
    {
        *beg_val++ = *(t_beg_val + index);
        *end_val-- = *(t_end_val - index);
        ++(*coord_x);
        pd_coord_update(n_shape, coord_x, n_shape_m, n_max, &index);
    }
    size_t *new_shape = pd_get_new_shape(tensor->shape, new_dim);
    size_t *new_shape_m = pd_tens_shape_mult(new_shape, shape_len);
    pd_arr_free(new_dim);
    return pd_tens_new(new_val, len, new_shape, new_shape_m, shape_len);
}
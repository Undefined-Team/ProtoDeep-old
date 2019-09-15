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
        if (t_index >= new_dim_len)
            pd_error("A dimension can't be greater than the number of dimensions (new_dim->val[i] < new_dim->length)");
        if (valid[t_index] == true)
            pd_error("2 dimensions can't have the same dimension");
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

static void         pd_coord_update(size_t *shape, size_t *coord)
{
    if (*coord == *shape)
    {
        *coord = 0;
        --coord;
        ++(*coord);
        pd_coord_update(shape - 1, coord);
    }
}

static void         pd_coord_update_2(size_t *n_shape, size_t *coord, size_t *n_shape_m, size_t *n_max, size_t *index)
{
    if (*coord == *n_shape)
    {
        *coord = 0;
        --coord;
        ++(*coord);
        *index -= *n_max;
        pd_coord_update_2(n_shape - 1, coord, n_shape_m - 1, n_max - 1, index);
    }
    else
        *index += *n_shape_m; // pas
}

static size_t     *pd_set_shape_shapem_max(size_t *old_shape, size_t *old_shape_m, size_t *new_dim, size_t *n_shape, size_t *n_shape_m, size_t shape_len)
{
    size_t *n_max;
    PD_PROT_MALLOC(n_max = pd_malloc(sizeof(size_t) * shape_len));

    size_t *tn_shape = n_shape;
    size_t *tn_shape_m = n_shape_m;
    size_t *tn_max = n_max;
    while (shape_len-- > 0)
    {
        *tn_shape   = old_shape[*new_dim];
        *tn_shape_m = old_shape_m[*new_dim++];
        *tn_max++   = (*tn_shape++ - 1) * *tn_shape_m++;
    }
    return n_max;
}

void        pd_tens_transpose(pd_tensor *tensor, pd_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = pd_error_manager(new_dim, shape_len);
    size_t len = tensor->len;
    size_t *coord;
    if (!(coord = pd_malloc(sizeof(size_t) * shape_len))) return ;

    size_t *coord_x = coord - 1;
    for (pd_count i = 0; i < shape_len; ++i) *++coord_x = 0;
    size_t *shape_x = tensor->shape + (shape_len - 1);

    float *new_val;
    if (!(new_val = pd_malloc(sizeof(float) * len))) return ;
    float *val = tensor->val;

    size_t *new_shape = pd_get_new_shape(tensor->shape, new_dim);
    size_t *new_shape_m = pd_tens_shape_mult(new_shape, shape_len);
    while (len-- > 0)
    {
        pd_coord_update(shape_x, coord_x);
        new_val[pd_get_index(shape_len, coord, t_new_dim, new_shape_m)] = *val++;
        ++(*coord_x);
    }
    pd_arr_free(new_dim);
    pd_free(coord);
    pd_free(tensor->val);
    pd_free(tensor->shape);
    pd_free(tensor->shape_m);
    tensor->val = new_val;
    tensor->shape = new_shape;
    tensor->shape_m = new_shape_m;
}

pd_tensor       *pd_tens_transpose_cpy_2(pd_tensor *tensor, pd_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = pd_error_manager(new_dim, shape_len);
    size_t len = tensor->len;

    size_t *b_shape;
    size_t *b_shape_m;
    PD_PROT_MALLOC(b_shape = pd_malloc(sizeof(size_t) * shape_len));
    PD_PROT_MALLOC(b_shape_m = pd_malloc(sizeof(size_t) * shape_len));
    size_t *b_max = pd_set_shape_shapem_max(tensor->shape, tensor->shape_m, t_new_dim, b_shape, b_shape_m, shape_len);

    size_t *n_shape = b_shape + (shape_len - 1);
    size_t *n_shape_m = b_shape_m + (shape_len - 1);
    size_t *n_max = b_max + (shape_len - 1);
    

    size_t *coord;
    PD_PROT_MALLOC(coord = pd_malloc(sizeof(size_t) * shape_len));
    size_t *coord_x = coord - 1;
    for (pd_count i = 0; i < shape_len; ++i) *++coord_x = 0;

    float *new_val;
    PD_PROT_MALLOC(new_val = pd_malloc(sizeof(float) * len));
    float *end_val = new_val;
    float *val = tensor->val;


    size_t index = 0;
    size_t tmp_len = len;
    while (tmp_len-- > 1)
    {
        *new_val++ = val[index];
        ++(*coord_x);
        pd_coord_update_2(n_shape, coord_x, n_shape_m, n_max, &index);
    }
    *new_val = val[len - 1];

    size_t *new_shape = pd_get_new_shape(tensor->shape, new_dim);
    size_t *new_shape_m = pd_tens_shape_mult(new_shape, shape_len);
    pd_arr_free(new_dim);
    pd_free(coord);
    pd_free(b_shape);
    pd_free(b_shape_m);
    pd_free(b_max);
    return pd_tens_new(end_val, len, new_shape, new_shape_m, shape_len);
}

pd_tensor       *pd_tens_transpose_cpy(pd_tensor *tensor, pd_size_t_a *new_dim)
{
    size_t shape_len = tensor->shape_len;
    size_t *t_new_dim = pd_error_manager(new_dim, shape_len);
    size_t len = tensor->len;

    size_t *coord;
    PD_PROT_MALLOC(coord = pd_malloc(sizeof(size_t) * shape_len));
    size_t *coord_x = coord - 1;
    for (pd_count i = 0; i < shape_len; ++i) *++coord_x = 0;
    size_t *shape_x = tensor->shape + (shape_len - 1);

    float *new_val;
    PD_PROT_MALLOC(new_val = pd_malloc(sizeof(float) * len));
    float *val = tensor->val;

    size_t *new_shape = pd_get_new_shape(tensor->shape, new_dim);
    size_t *new_shape_m = pd_tens_shape_mult(new_shape, shape_len);
    while (len-- > 0)
    {
        pd_coord_update(shape_x, coord_x);
        new_val[pd_get_index(shape_len, coord, t_new_dim, new_shape_m)] = *val++;
        ++(*coord_x);
    }
    pd_arr_free(new_dim);
    pd_free(coord);
    return pd_tens_new(new_val, len, new_shape, new_shape_m, shape_len);
}
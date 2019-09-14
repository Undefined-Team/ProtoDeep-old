#include "pd_main.h"

static size_t *pd_tens_comp_coord(size_t *coord, size_t len, size_t real_len)
{
    size_t *new_coord;
    PD_PROT_MALLOC(new_coord = pd_malloc(sizeof(size_t) * real_len));
    size_t *new_coord_tmp = new_coord;
    real_len -= len;
    while (len--) *new_coord_tmp++ = *coord++;
    while (real_len--) *new_coord_tmp++ = 0;
    return new_coord;
}

pd_tensor *pd_tens_get(pd_tensor *tensor, pd_size_t_a *coord)
{
    size_t coord_len = coord->len;
    size_t shape_len = tensor->shape_len;
    if (coord_len == shape_len) pd_error("This function can't return a float. Use pd_tens_get_val instead.");
    else if (coord_len > shape_len) pd_error("Coord can't have more axis than tennsor");
    else if (coord_len == 0) pd_error("Coord can't be empty");
    size_t *real_coord = pd_tens_comp_coord(coord->val, coord_len, shape_len);
    pd_tensor *child = pd_tens_new(pd_tens_get_pval(tensor, real_coord), tensor->shape_m[coord_len - 1],
    tensor->shape + coord_len, tensor->shape_m + coord_len, shape_len - coord_len);
    pd_arr_free(coord);
    pd_free(real_coord);
    return child;
}

pd_tensor *pd_tens_get_cpy(pd_tensor *tensor, pd_size_t_a *coord)
{
    pd_tensor *get_tensor = pd_tens_get(tensor, coord);
    pd_tensor *new_tensor = pd_tens_cpy(get_tensor);
    pd_free(get_tensor);
    return (new_tensor);
}
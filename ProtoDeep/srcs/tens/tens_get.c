#include "pd_main.h"

static size_t *pd_tens_comp_coord(size_t *coord, size_t len, size_t real_len)
{
    size_t *new_coord;
    PD_PROT_MALLOC(new_coord = pd_malloc(sizeof(size_t) * real_len));
    size_t *new_coord_tmp;
    pd_count i = 0;
    while (i < len) *new_coord_tmp++ = *coord++;
    while (i < real_len) *new_coord_tmp++ = 0;
    return new_coord;
}

pd_tensor *pd_tens_get(pd_tensor *tensor, pd_size_t_a *coord)
{
    size_t coord_len = coord->len;
    size_t shape_len = tensor->shape_len;
    if (coord_len == shape_len) pd_error("This function can't return a float. Use pd_tens_get_val instead.");
    else if (coord_len > shape_len) pd_error("Coord can't have more axis than tennsor");
    else if (coord_len == 0) pd_error("Coord can't be empty");
    pd_tensor *child;
    PD_PROT_MALLOC(child = pd_malloc(sizeof(pd_tensor)));
    child->len = child->shape_m[coord_len - 1];
    child->shape = child->shape + coord_len;
    child->shape_m = child->shape_m + coord_len;
    size_t *real_coord = pd_tens_comp_coord(coord->val, coord_len, shape_len);
    child->val = pd_tens_get_pval(tensor, real_coord);
    return child;
}

// pd_tensor *pd_tens_get_cpy()
// {

// }
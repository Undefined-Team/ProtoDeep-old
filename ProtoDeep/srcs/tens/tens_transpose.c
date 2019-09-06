#include "pd_main.h"

pd_size_t_a     pd_get_new_shape(pd_size_t_a shape, pd_size_t_a new_dim)
{
    pd_size_t_a new_shape = pd_arr_init(PD_T_SIZE_T, shape.len);
    for (size_t i = 0; i < shape.len; i++)
        ((size_t*)new_shape.val)[i] = ((size_t*)shape.val)[((size_t*)new_dim.val)[i]];
    return new_shape;
}

pd_size_t_a     pd_get_shape_mult(pd_size_t_a new_shape)
{
    pd_size_t_a shape_mult = pd_arr_init(PD_T_SIZE_T, new_shape.len);
    ((size_t*)shape_mult.val)[shape_mult.len - 1] = 1;
    for (size_t i = shape_mult.len - 1; i > 0; i--)
        ((size_t*)shape_mult.val)[i - 1] = ((size_t*)new_shape.val)[i] * ((size_t*)shape_mult.val)[i];
    return shape_mult;
}

size_t          pd_get_index(pd_size_t_a coord, pd_size_t_a new_dim, pd_size_t_a shape_mult)
{
    size_t index = 0;
    for (size_t i = 0; i < coord.len; i++)
        index += ((size_t*)coord.val)[((size_t*)new_dim.val)[i]] * ((size_t*)shape_mult.val)[i];
    return index;
}

pd_size_t_a     pd_get_coord(size_t reste, pd_size_t_a shape_mult)
{
    pd_size_t_a coord = pd_arr_init(PD_T_SIZE_T, shape_mult.len);
    size_t quot;
    for (size_t i = 0; i < coord.len; i++)
    {
        ((size_t*)coord.val)[i] = reste / ((size_t*)shape_mult.val)[i];
        reste = reste % ((size_t*)shape_mult.val)[i];
    }
    return coord;
}

pd_tensor       pd_tens_transpose(pd_tensor tensor, pd_size_t_a new_dim)
{
    //pd_arr_print(new_dim);
    pd_size_t_a new_shape = pd_get_new_shape(tensor.shape, new_dim);
    //pd_arr_print(new_shape);
    pd_size_t_a shape_mult = pd_get_shape_mult(new_shape);
    //pd_arr_print(shape_mult);
    pd_tensor flatten = pd_tens_flatten(tensor);
    //printf("SALUT\n");
    //pd_tens_print(flatten);
    //pd_arr_print(flatten.shape);
    pd_arr_print(flatten.shape);
    pd_tensor new_flatten = pd_tens_init(flatten.shape);
    printf(">> premier passage\n");
    pd_arr_print(new_flatten.shape);
    //pd_arr_print(new_flatten.shape);
    //pd_tens_print(new_flatten);
    for (size_t i = 0; i < flatten.len; i++)
    {
        //printf("----------\n%zd = ", i);
        //pd_arr_print(pd_get_coord(i, shape_mult));
        //printf("new i = %zd\n", pd_get_index(pd_get_coord(i, shape_mult), new_dim, shape_mult));
        if (pd_get_index(pd_get_coord(i, shape_mult), new_dim, shape_mult) < new_flatten.len)
        ((float*)new_flatten.val)[pd_get_index(pd_get_coord(i, shape_mult), new_dim, shape_mult)] = ((float*)flatten.val)[i];
    }
    //pd_tens_print(new_flatten);
    printf(">> deuxieme passage\n");
    pd_arr_print(new_flatten.shape);
    pd_tensor transpose_tensor = pd_tens_reshape(new_flatten, new_shape);
    pd_tens_free(flatten);
    pd_tens_free(new_flatten);
    return transpose_tensor;
}
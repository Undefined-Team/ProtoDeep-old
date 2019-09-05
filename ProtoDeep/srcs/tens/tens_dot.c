#include "pd_main.h"

size_t g_debug_len = 0;

void        print_pd_arr(pd_arr arr)
{
    for (size_t i = 0; i < arr.len; i++)
    {
        printf("%zd, ", ((size_t *)arr.val)[i]);
    }
    printf("\n");
}

void        print_size_t_arr(size_t *arr, size_t len)
{
    printf("[");
    for (size_t i = 0; i < (len ? len : g_debug_len); i++)
    {
        printf("%zd, ", arr[i]);
    }
    printf("]");
    printf("\n");
}

size_t      *pd_tens_get_dot_shape(pd_arr a_shape, pd_arr b_shape, size_t len)
{
    size_t      *result_shape;
    size_t      j = 0;

    result_shape = (size_t *)malloc(len * sizeof(size_t));
    for (size_t i = 0; i < a_shape.len; i++)
        if (((size_t *)a_shape.val)[i])
            result_shape[j++] = ((size_t *)a_shape.val)[i];
    for (size_t i = 0; i < b_shape.len; i++)
        if (((size_t *)b_shape.val)[i])
            result_shape[j++] = ((size_t *)b_shape.val)[i];
    return (result_shape);
}

pd_tensor   pd_tens_init_dot_result(pd_arr a_shape, pd_arr b_shape, size_t *axis[2])
{
    size_t      rank;
    size_t      count = 0;
    size_t      *result_shape;
    size_t      len = 0;
    pd_tensor   result;

    //to do : The axis a_axes[i] of a must have the same dimension as axis b_axes[i] of b for all i in range(0, len(a_axes))
    rank = a_shape.len + b_shape.len - (2 * 2 /*axis len */);
    for (size_t i = 0; i < 2 /* axis len */; i++)
    {
        ((size_t *)a_shape.val)[axis[0][i]] = 0;
        ((size_t *)b_shape.val)[axis[1][i]] = 0;
        count += 2;
    }
    len = (a_shape.len + b_shape.len) - count;
    result_shape = pd_tens_get_dot_shape(a_shape, b_shape, len);
    result = pd_tens_init(result_shape, len);
    return (result);
}

// pd_tensor    pd_tens_dot(pd_tensor a, pd_tensor b, size_t *axis[2])
// {
//     pd_tensor   result;
//     size_t      *shape;
//     size_t      *pos;

//     result = pd_tens_init_dot_result(pd_tens_get_shape(a), pd_tens_get_shape(b), axis);
//     pos = (size_t *)malloc(result.shape.len * sizeof(float));
//     for (size_t i = 0; i < result.shape.len; i++)
//         pos[i] = 0;
//     g_debug_len = result.shape.len;
//     // for (size_t i = 0; i < ((size_t *)result.shape.val)[0]; i++)
//     //     result = pd_tens_dot_product(a, b);
// }

pd_tensor    pd_tens_dot(pd_tensor a, pd_tensor b, pd_size_t_a axis)
{
    pd_arr_print(axis);
}
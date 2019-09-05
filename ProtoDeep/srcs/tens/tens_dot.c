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

pd_tensor    pd_tens_dot(pd_tensor a, pd_tensor b, pd_arr axis)
{
    pd_size_t_a     shape_a;
    pd_size_t_a     shape_b;
    size_t          j_a = 0;
    size_t          j_b = 0;
    size_t          n_a = 1;
    size_t          n_b = 1;
    size_t          m_a = 1;
    size_t          m_b = 1;
    pd_size_t_a     old_a;
    pd_size_t_a     old_b;
    pd_size_t_a     new_a;
    pd_size_t_a     new_b;

    shape_a = pd_arr_init(PD_T_SIZE_T, a.shape.len - ((pd_arr *)axis.val)[0].len);
    shape_b = pd_arr_init(PD_T_SIZE_T, b.shape.len - ((pd_arr *)axis.val)[1].len);
    for (size_t i = 0; i < a.shape.len; i++)
    {
        bool    in_axis_a = false;
        bool    in_axis_b = false;
        for (size_t k = 0; k < ((pd_arr *)axis.val)[0].len && (!in_axis_a || !in_axis_b); k++)
        {
            if (i == ((size_t *)((pd_arr *)axis.val)[0].val)[k])
                in_axis_a = true;
            if (i == ((size_t *)((pd_arr *)axis.val)[1].val)[k])
                in_axis_b = true;
        }
        if (!in_axis_a)
            ((size_t *)shape_a.val)[j_a++] = i;
        if (!in_axis_b)
            ((size_t *)shape_b.val)[j_b++] = i;
    }
    for (size_t i = 0; i < ((pd_arr *)axis.val)[0].len; i++)
    {
        n_a *= ((size_t *)a.shape.val)[((size_t *)((pd_arr *)axis.val)[0].val)[i]];
        n_b *= ((size_t *)b.shape.val)[((size_t *)((pd_arr *)axis.val)[1].val)[i]];
    }
    old_a = pd_arr_init(PD_T_SIZE_T, shape_a.len);
    old_b = pd_arr_init(PD_T_SIZE_T, shape_b.len);
    for (size_t i = 0; i < shape_a.len; i++)
    {
        size_t val_a = ((size_t *)a.shape.val)[((size_t *)shape_a.val)[i]];
        size_t val_b = ((size_t *)b.shape.val)[((size_t *)shape_b.val)[i]];
        printf("%zd [%zd]\n%zd [%zd]\n\n", val_a, ((size_t *)shape_a.val)[i], val_b, ((size_t *)shape_b.val)[i]);
        m_a *= val_a;
        m_b *= val_b;
        ((size_t *)old_a.val)[i] = val_a;
        ((size_t *)old_b.val)[i] = val_b;
    }
    new_a = pd_arr_init(PD_T_SIZE_T, 2);
    new_b = pd_arr_init(PD_T_SIZE_T, 2);
    ((size_t *)new_a.val)[0] = m_a;
    ((size_t *)new_a.val)[1] = n_a;
    ((size_t *)new_b.val)[0] = n_b;
    ((size_t *)new_b.val)[1] = m_b;
    pd_arr_print(a.shape);
    pd_arr_print(b.shape);
    pd_arr_print(shape_a);
    pd_arr_print(shape_b);
    pd_arr_print(axis);
    pd_arr_print(new_a);
    pd_arr_print(new_b);
    printf("n_a: %zd, n_b: %zd\n", n_a, n_b);
    pd_tensor t_a = pd_tens_transpose(a, new_axes_a;
    pd_tensor t_b = pd_tens_transpose(b, new_axes_b);
    t_a = pd_tens_reshape(t_a, new_a);
    t_b = pd_tens_reshape(t_b, new_b);
    pd_tensor res = pd_matrix_dot(t_a, t_b);
    res = pd_tens_reshape(old_a, old_b);
    return (res);
}
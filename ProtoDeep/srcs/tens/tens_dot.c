#include "pd_main.h"

pd_arr      pd_tens_get_counter_axis(size_t len, pd_arr axis)
{
    size_t          j_a = 0;
    size_t          j_b = 0;
    pd_arr          counter_axis;
    
    counter_axis = pd_arr_init(PD_T_ARR, 2);
    ((pd_arr *)counter_axis.val)[0] = pd_arr_init(PD_T_SIZE_T, len - ((pd_arr *)axis.val)[0].len);
    ((pd_arr *)counter_axis.val)[1] = pd_arr_init(PD_T_SIZE_T, len - ((pd_arr *)axis.val)[0].len);
    for (size_t i = 0; i < len; i++)
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
            ((size_t *)((pd_arr *)counter_axis.val)[0].val)[j_a++] = i;
        if (!in_axis_b)
            ((size_t *)((pd_arr *)counter_axis.val)[1].val)[j_b++] = i;
    }
    return (counter_axis);
}

pd_arr   pd_tens_get_new_axes(pd_size_t_a n, pd_size_t_a m, pd_arr counter_axis, pd_arr axis)
{
    pd_arr          new_axes = pd_arr_init(PD_T_ARR, 2);

    ((pd_arr *)new_axes.val)[0] = pd_arr_init(PD_T_SIZE_T, ((pd_arr *)counter_axis.val)[0].len + ((pd_arr *)axis.val)[0].len);
    ((pd_arr *)new_axes.val)[1] = pd_arr_init(PD_T_SIZE_T, ((pd_arr *)counter_axis.val)[1].len + ((pd_arr *)axis.val)[1].len);
    for (size_t i = 0; i < ((pd_arr *)counter_axis.val)[0].len; i++)
    {
        ((size_t *)((pd_arr *)new_axes.val)[0].val)[i] = ((size_t *)((pd_arr *)counter_axis.val)[0].val)[i];
        ((size_t *)((pd_arr *)new_axes.val)[1].val)[i] = ((size_t *)((pd_arr *)counter_axis.val)[1].val)[i];
    }
    for (size_t i = ((pd_arr *)counter_axis.val)[0].len; i < ((pd_arr *)counter_axis.val)[0].len + ((pd_arr *)axis.val)[0].len; i++)
    {
        ((size_t *)((pd_arr *)new_axes.val)[0].val)[i] = ((size_t *)((pd_arr *)axis.val)[0].val)[i - ((pd_arr *)counter_axis.val)[0].len];
        ((size_t *)((pd_arr *)new_axes.val)[1].val)[i] = ((size_t *)((pd_arr *)axis.val)[1].val)[i - ((pd_arr *)counter_axis.val)[0].len];
    }
    return (new_axes);
}

pd_tensor   pd_tens_get_res(pd_tensor a, pd_tensor b, pd_arr new_axes, pd_size_t_a m, pd_size_t_a n, pd_arr old)
{
    pd_tensor t_a = pd_tens_transpose(a, ((pd_arr *)new_axes.val)[0]);
    pd_tensor t_b = pd_tens_transpose(b, ((pd_arr *)new_axes.val)[1]);
    pd_arr new = pd_arr_create(pd_arr_shape(2, 2, 2), PD_T_SIZE_T, ((size_t *)m.val)[0], ((size_t *)n.val)[0], ((size_t *)n.val)[1], ((size_t *)m.val)[1]);
    pd_tensor res;
    pd_arr old_concat;

    t_a = pd_tens_reshape(t_a, ((pd_arr *)new.val)[0]);
    t_b = pd_tens_reshape(t_b, ((pd_arr *)new.val)[1]);
    res = pd_matrix_dot(t_a, t_b);
    old_concat = pd_arr_shape_concat(((pd_arr *)old.val)[0], ((pd_arr *)old.val)[1]);
    res = pd_tens_reshape(res, old_concat);
    return (res);
}

pd_tensor    pd_tens_dot(pd_tensor a, pd_tensor b, pd_arr axis)
{
    pd_arr          counter_axis;
    pd_size_t_a     n = pd_arr_create(pd_arr_shape(1, 2), PD_T_SIZE_T, 1, 1);
    pd_size_t_a     m = pd_arr_create(pd_arr_shape(1, 2), PD_T_SIZE_T, 1, 1);
    pd_arr          old = pd_arr_init(PD_T_ARR, 2);
    pd_arr          new_axes;

    counter_axis = pd_tens_get_counter_axis(a.shape.len, axis);
    for (size_t i = 0; i < ((pd_arr *)axis.val)[0].len; i++)
    {
        ((size_t *)n.val)[0] *= ((size_t *)a.shape.val)[((size_t *)((pd_arr *)axis.val)[0].val)[i]];
        ((size_t *)n.val)[1] *= ((size_t *)b.shape.val)[((size_t *)((pd_arr *)axis.val)[1].val)[i]];
    }
    ((pd_arr *)old.val)[0] = pd_arr_init(PD_T_SIZE_T, ((pd_arr *)counter_axis.val)[0].len);
    ((pd_arr *)old.val)[1] = pd_arr_init(PD_T_SIZE_T, ((pd_arr *)counter_axis.val)[1].len);
    for (size_t i = 0; i < ((pd_arr *)counter_axis.val)[0].len; i++)
    {
        size_t val_a = ((size_t *)a.shape.val)[((size_t *)((pd_arr *)counter_axis.val)[0].val)[i]];
        size_t val_b = ((size_t *)b.shape.val)[((size_t *)((pd_arr *)counter_axis.val)[1].val)[i]];
        ((size_t *)m.val)[0] *= val_a;
        ((size_t *)m.val)[1] *= val_b;
        ((size_t *)((pd_arr *)old.val)[0].val)[i] = val_a;
        ((size_t *)((pd_arr *)old.val)[1].val)[i] = val_b;
    }
    new_axes = pd_tens_get_new_axes(n, m, counter_axis, axis);
    return (pd_tens_get_res(a, b, new_axes, m, n, old));
}
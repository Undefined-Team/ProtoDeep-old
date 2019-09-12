#include "pd_main.h"

pd_arr      *pd_tens_get_counter_axis(size_t len, pd_arr *axis)
{
    size_t          j_a = 0;
    size_t          j_b = 0;
    pd_arr          *counter_axis;
    
    counter_axis = pd_arr_init(PD_T_ARR, 2);
    ((pd_arr **)counter_axis->val)[0] = pd_arr_init(PD_T_SIZE_T, len - ((pd_arr **)axis->val)[0]->len);
    ((pd_arr **)counter_axis->val)[1] = pd_arr_init(PD_T_SIZE_T, len - ((pd_arr **)axis->val)[0]->len);

    size_t *t_axis_a_val = (size_t *)((pd_arr **)axis->val)[0]->val;
    size_t *t_axis_b_val = (size_t *)((pd_arr **)axis->val)[1]->val;
    size_t *t_counter_axis_a_val = (size_t *)((pd_arr **)counter_axis->val)[0]->val;
    size_t *t_counter_axis_b_val = (size_t *)((pd_arr **)counter_axis->val)[1]->val;

    for (size_t i = 0; i < len; i++)
    {
        bool    in_axis_a = false;
        bool    in_axis_b = false;
        for (size_t k = 0; k < ((pd_arr **)axis->val)[0]->len && (!in_axis_a || !in_axis_b); k++)
        {
            if (i == t_axis_a_val[k])
                in_axis_a = true;
            if (i == t_axis_b_val[k])
                in_axis_b = true;
        }
        if (!in_axis_a)
            t_counter_axis_a_val[j_a++] = i;
        if (!in_axis_b)
            t_counter_axis_b_val[j_b++] = i;
    }
    return (counter_axis);
}

pd_arr      *pd_tens_dot_shape_mult(pd_tensor *a, pd_tensor *b, pd_arr *axis, pd_arr *counter_axis, pd_arr *mem_shapes)
{
    pd_arr  *shape_mult = pd_arr_init(PD_T_ARR, 2);
    size_t axis_len = ((pd_arr **)axis->val)[0]->len;
    size_t counter_axis_len = a->shape->len - ((pd_arr **)axis->val)[0]->len;
    
    size_t *t_a_shape_val = (size_t *)a->shape->val;
    size_t *t_b_shape_val = (size_t *)b->shape->val;
    size_t *t_axis_a_val = (size_t *)((pd_arr **)axis->val)[0]->val;
    size_t *t_axis_b_val = (size_t *)((pd_arr **)axis->val)[1]->val;
    size_t n_a = 1;
    size_t n_b = 1;
    for (size_t i = 0; i < axis_len; i++)
    {
        n_a *= t_a_shape_val[t_axis_a_val[i]];
        n_b *= t_b_shape_val[t_axis_b_val[i]];
    }
    size_t *t_counter_axis_a_val = (size_t *)((pd_arr **)counter_axis->val)[0]->val;
    size_t *t_counter_axis_b_val = (size_t *)((pd_arr **)counter_axis->val)[1]->val;
    size_t *t_mem_shapes_val = (size_t *)mem_shapes->val;
    size_t m_a = 1;
    size_t m_b = 1;
    for (size_t i = 0; i < counter_axis_len; i++)
    {
        size_t val_a = t_a_shape_val[t_counter_axis_a_val[i]];
        size_t val_b = t_b_shape_val[t_counter_axis_b_val[i]];
        m_a *= val_a;
        m_b *= val_b;
        t_mem_shapes_val[i] = val_a;
        t_mem_shapes_val[i + counter_axis_len] = val_b;
    }
    ((pd_arr **)shape_mult->val)[0] = pd_arr_shape(2, m_a, n_a);
    ((pd_arr **)shape_mult->val)[1] = pd_arr_shape(2, n_b, m_b);
    return (shape_mult);
}

pd_tensor   *pd_tens_dot(pd_tensor *a, pd_tensor *b, pd_arr *axis)
{
    pd_arr *shape_mult;
    pd_arr *counter_axis;
    size_t  tens_len = a->shape->len;
    size_t  axis_len = ((pd_arr **)axis->val)[0]->len;
    pd_arr *mem_shapes = pd_arr_init(PD_T_SIZE_T, (tens_len - axis_len) * 2);
    
    counter_axis = (tens_len > axis_len ? pd_tens_get_counter_axis(a->shape->len, axis) : NULL);
    shape_mult = pd_tens_dot_shape_mult(a, b, axis, counter_axis, mem_shapes);
    pd_arr *new_dim_a = pd_arr_concat_shape(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[0], ((pd_arr **)axis->val)[0]);
    pd_arr *new_dim_b = pd_arr_concat_shape(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[1], ((pd_arr **)axis->val)[1]);
    pd_tensor *t_a = pd_tens_transpose(a, new_dim_a);
    pd_tensor *t_b = pd_tens_transpose(b, new_dim_b);
    pd_tensor *reshape_t_a = pd_tens_reshape(t_a, ((pd_arr **)shape_mult->val)[0]);
    pd_tensor *reshape_t_b = pd_tens_reshape(t_b, ((pd_arr **)shape_mult->val)[1]);
    pd_tensor *dot_res = pd_matrix_dot(reshape_t_a, reshape_t_b);
    pd_tensor *res = pd_tens_reshape(dot_res, mem_shapes);
    return (res);
}
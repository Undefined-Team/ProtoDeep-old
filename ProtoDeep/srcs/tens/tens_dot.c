#include "pd_main->h"

pd_arr      *pd_tens_get_counter_axis(size_t len, pd_arr *axis)
{
    size_t          j_a = 0;
    size_t          j_b = 0;
    pd_arr          counter_axis;
    
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

pd_arr   *pd_tens_get_new_axes(pd_arr *counter_axis, pd_arr *axis)
{
    pd_arr          new_axes = pd_arr_init(PD_T_ARR, 2);

    ((pd_arr **)new_axes->val)[0] = pd_arr_init(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[0]->len + ((pd_arr **)axis->val)[0]->len);
    ((pd_arr **)new_axes->val)[1] = pd_arr_init(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[1]->len + ((pd_arr **)axis->val)[1]->len);

    size_t *new_axes_a_val = (size_t *)((pd_arr **)new_axes->val)[0];
    size_t *new_axes_b_val = (size_t *)((pd_arr **)new_axes->val)[1];

    for (size_t i = 0; i < ((pd_arr **)counter_axis->val)[0]->len; i++)
    {
        new_axes_a_val[i] = t_counter_axis_a_val[i];
        new_axes_b_val[i] = t_counter_axis_b_val[i];
    }

    size_t *counter_axis_len = ((pd_arr **)counter_axis->val)[0]->len;

    for (size_t i = counter_axis_len; i < counter_axis_len + ((pd_arr **)axis->val)[0]->len; i++)
    {
        new_axes_a_val[i] = t_axis_a_val[i - counter_axis_len];
        new_axes_b_val[i] = t_axis_b_val[i - counter_axis_len];
    }
    return (new_axes);
}

pd_tensor   *pd_tens_get_res(pd_tensor *a, pd_tensor *b, pd_arr *new_axes, pd_size_t_a *m, pd_size_t_a *n, pd_arr *old)
{
    pd_tensor *t_a = pd_tens_transpose(a, ((pd_arr **)new_axes->val)[0]);
    pd_tensor *t_b = pd_tens_transpose(b, ((pd_arr **)new_axes->val)[1]);
    pd_arr *new = pd_arr_create(pd_arr_shape(2, 2, 2), PD_T_SIZE_T, ((size_t *)m->val)[0], ((size_t *)n->val)[0], ((size_t *)n->val)[1], ((size_t *)m->val)[1]);
    pd_tensor *dot_res;
	pd_tensor *res;
    pd_arr *old_concat;
    pd_tensor *reshape_t_a = pd_tens_reshape(t_a, ((pd_arr **)new->val)[0]);
    pd_tensor *reshape_t_b = pd_tens_reshape(t_b, ((pd_arr **)new->val)[1]);

    dot_res = pd_matrix_dot(reshape_t_a, reshape_t_b);
    old_concat = pd_arr_concat_shape(PD_T_SIZE_T, ((pd_arr **)old->val)[0], ((pd_arr **)old->val)[1]);
    res = pd_tens_reshape(dot_res, old_concat);
	pd_tens_free(dot_res);
	pd_tens_free(t_a);
	pd_tens_free(t_b);
	pd_tens_free(reshape_t_a);
	pd_tens_free(reshape_t_b);
	pd_free(((pd_arr **)old->val)[0]->val);
	pd_free(((pd_arr **)old->val)[1]->val);
	pd_free(old->val);
	pd_arr_free(new);
	pd_arr_free(new_axes);
	pd_arr_free(m);
	pd_arr_free(n);
	return (res);
}

pd_tensor    pd_tens_dot(pd_tensor *a, pd_tensor *b, pd_arr axis)
{
    pd_arr          *counter_axis;
    pd_size_t_a     *n = pd_arr_create(pd_arr_shape(1, 2), PD_T_SIZE_T, 1, 1);
    pd_size_t_a     *m = pd_arr_create(pd_arr_shape(1, 2), PD_T_SIZE_T, 1, 1);
    pd_arr          *old = pd_arr_init(PD_T_ARR, 2);
    pd_arr          *new_axes;

    size_t *t_n_val = (size_t *)n->val;
    size_t *t_m_val = (size_t *)m->val;
    size_t *t_a_shape_val = (size_t *)a->shape->val;
    size_t *t_b_shape_val = (size_t *)b->shape->val;
    size_t *t_axis_a_val = (size_t *)((pd_arr **)axis->val)[0]->val;
    size_t *t_axis_b_val = (size_t *)((pd_arr **)axis->val)[1]->val;

    counter_axis = pd_tens_get_counter_axis(a->shape->len, axis);
    for (size_t i = 0; i < ((pd_arr **)axis->val)[0]->len; i++)
    {
        t_n_val[0] *= t_a_shape_val[t_axis_a_val[i]];
        t_n_val[1] *= t_b_shape_val[t_axis_b_val[i]];
    }
    ((pd_arr **)old->val)[0] = pd_arr_init(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[0]->len);
    ((pd_arr **)old->val)[1] = pd_arr_init(PD_T_SIZE_T, ((pd_arr **)counter_axis->val)[1]->len);

    size_t *t_counter_axis_a_val = (size_t *)((pd_arr **)counter_axis->val)[0]->val;
    size_t *t_counter_axis_b_val = (size_t *)((pd_arr **)counter_axis->val)[1]->val;
    size_t *t_old_a_val = (size_t *)((pd_arr **)old->val)[0]->val;
    size_t *t_old_b_val = (size_t *)((pd_arr **)old->val)[1]->val;

    for (size_t i = 0; i < ((pd_arr **)counter_axis->val)[0]->len; i++)
    {
        size_t val_a = t_a_shape_val[t_counter_axis_a_val[i]];
        size_t val_b = t_b_shape_val[t_counter_axis_b_val[i]];
        t_m_val[0] *= val_a;
        t_m_val[1] *= val_b;
        t_old_a_val[i] = val_a;
        t_old_b_val[i] = val_b;
    }
    new_axes = pd_tens_get_new_axes(counter_axis, axis);
	pd_free(((pd_arr **)axis->val)[0]->val);
	pd_free(((pd_arr **)axis->val)[1]->val);
	pd_free(axis->val);
	pd_free(((pd_arr **)counter_axis->val)[0]->val);
	pd_free(((pd_arr **)counter_axis->val)[1]->val);
	pd_free(counter_axis->val);
    return (pd_tens_get_res(a, b, new_axes, m, n, old));
}

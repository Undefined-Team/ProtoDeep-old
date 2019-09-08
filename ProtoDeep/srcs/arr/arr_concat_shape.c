#include "pd_main.h"

pd_arr      *pd_arr_concat_shape(pd_type type, pd_arr *a, pd_arr *b)
{
    pd_arr      *c = pd_arr_init(type, a->len + b->len);

    if (type == PD_T_FLOAT)
    {
        float *t_a_val = (float *)a->val;
        float *t_b_val = (float *)b->val;
        float *t_c_val = (float *)c->val;
        for (size_t i = 0; i < a->len; i++) t_c_val[i] = t_a_val[i];
        for (size_t i = a->len; i < a->len + b->len; i++) t_c_val[i] = t_b_val[i - a->len];
    }
    else if (type == PD_T_SIZE_T)
    {
        size_t *t_a_val = (size_t *)a->val;
        size_t *t_b_val = (size_t *)b->val;
        size_t *t_c_val = (size_t *)c->val;
        for (size_t i = 0; i < a->len; i++) t_c_val[i] = t_a_val[i];
        for (size_t i = a->len; i < a->len + b->len; i++) t_c_val[i] = t_b_val[i - a->len];
    }
    else if (type == PD_T_CHAR)
    {
        char *t_a_val = (char *)a->val;
        char *t_b_val = (char *)b->val;
        char *t_c_val = (char *)c->val;
        for (size_t i = 0; i < a->len; i++) t_c_val[i] = t_a_val[i];
        for (size_t i = a->len; i < a->len + b->len; i++) t_c_val[i] = t_b_val[i - a->len];
    }
    return (c);
}

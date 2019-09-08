#include "pd_main.h"

pd_size_t_a       *pd_arr_get_shape(pd_arr *shape)
{
    pd_size_t_a   *buffer;

    buffer = pd_str_new_s("[");
    size_t *t_shape_val = (size_t *)shape->val;
    for (size_t i = 0; i < shape->len; i++)
    {
        buffer = pd_str_join(buffer, pd_math_itoa(t_shape_val[i]));
        if (i != shape->len - 1)
            buffer = pd_str_join(buffer, pd_str_new_s(", "));
    }
    buffer = pd_str_join(buffer, pd_str_new_s("]"));
    return (buffer);
}
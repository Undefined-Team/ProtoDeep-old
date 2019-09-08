#include "pd_main.h"

pd_char_a       pd_arr_get_shape(pd_arr shape)
{
    pd_char_a   buffer;

    buffer = pd_str_new_s("[");
    for (size_t i = 0; i < shape.len; i++)
    {
        buffer = pd_str_join(buffer, pd_math_itoa(((size_t *)shape.val)[i]));
        if (i != shape.len - 1)
            buffer = pd_str_join(buffer, pd_str_new_s(", "));
    }
    buffer = pd_str_join(buffer, pd_str_new_s("]"));
    return (buffer);
}
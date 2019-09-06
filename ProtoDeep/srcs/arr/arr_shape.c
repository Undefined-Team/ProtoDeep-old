#include "pd_main.h"

pd_size_t_a     pd_arr_shape(size_t len, ...)
{
    va_list     va;
    pd_size_t_a shape;
    
    shape = pd_arr_init(PD_T_SIZE_T, len);
    if (!len)
    {
        shape.val = NULL;
        return (shape);
    }
    va_start(va, len);
    for (size_t i = 0; i < len; i++)
        ((size_t *)shape.val)[i] = (size_t)va_arg(va, int);
    va_end(va);
    return (shape);
}
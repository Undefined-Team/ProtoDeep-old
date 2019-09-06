#include "pd_main.h"

pd_size_t_a pd_tens_shape(size_t len, int dim, ...)
{
    va_list     va;
    pd_size_t_a shape;
    
    shape = malloc(len * sizeof(size_t));
    ((size_t *)shape.val)[0] = (size_t)dim;
    va_start(va, dim);
    for (size_t i = 1; i < len; i++)
    {
        ((size_t *)shape.val)[i] = (size_t)va_arg(va, int);
    }
    va_end(va);
    return (shape);
}
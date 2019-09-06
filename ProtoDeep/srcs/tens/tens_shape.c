#include "pd_main.h"

size_t  *pd_tens_shape(size_t len, int dim, ...)
{
    va_list     va;
    size_t      *shape;
    
    shape = malloc(len * sizeof(size_t));
    shape[0] = (size_t)dim;
    va_start(va, dim);
    for (size_t i = 1; i < len; i++)
    {
        shape[i] = (size_t)va_arg(va, int);
    }
    va_end(va);
    return (shape);
}
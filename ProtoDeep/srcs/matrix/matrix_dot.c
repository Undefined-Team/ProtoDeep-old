#include "pd_main.h"

pd_tensor   pd_matrix_dot(pd_tensor a, pd_tensor b)
{
    pd_tensor   result;

    if (a.shape.len != 2 || b.shape.len != 2)
        pd_error("Can't do matrix dot product on tensor with %zd dimensions and tensor with %zd dimensions.\n", a.shape.len, b.shape.len);
    else if (((size_t *)a.shape.val)[0] != ((size_t *)b.shape.val)[1])
        pd_error("Matrix [%zd, %zd] incompatible with matrix [%zd, %zd].\n", ((size_t *)a.shape.val)[0],
        ((size_t *)a.shape.val)[1], ((size_t *)b.shape.val)[0], ((size_t *)b.shape.val)[1]);
    result = pd_tens_init(pd_tens_shape(2, ((size_t *)a.shape.val)[1], ((size_t *)b.shape.val)[0]), 2);
    pd_tens_print(result);
    for (size_t i = 0; i < ((size_t *)a.shape.val)[1]; i++)
    {
        float sum = 0;
        for (size_t j = 0; j < ((size_t *)b.shape.val)[0]; j++)
            sum += ((float *)((pd_tensor *)a.val)[i].val)[j] * ((float *)((pd_tensor *)b.val)[j].val)[i];
    }
    return (result);
}
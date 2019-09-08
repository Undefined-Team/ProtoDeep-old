#include "pd_main.h"

/*pd_tensor   pd_matrix_dot(pd_tensor a, pd_tensor b)
{
    pd_tensor   result;
    size_t      x_a = ((size_t *)a.shape.val)[0];
    size_t      x_b = ((size_t *)b.shape.val)[0];
    size_t      y_a = ((size_t *)a.shape.val)[1];
    size_t      y_b = ((size_t *)b.shape.val)[1];

    if (a.shape.len != 2 || b.shape.len != 2)
        pd_error("Can't do matrix dot product on tensor with %zd dimensions and tensor with %zd dimensions.\n", a.shape.len, b.shape.len);
    else if (y_a != x_b)
        pd_error("Matrix [%zd, %zd] incompatible with matrix [%zd, %zd].\n", x_a, y_a, x_b, y_b);
    result = pd_tens_init(pd_arr_shape(2, x_a, y_b));
    for (size_t k = 0; k < x_a; k++)
        for (size_t l = 0; l < y_b; l++)
        {
            float sum = 0;
            for (size_t j = 0; j < y_a; j++)
                sum += ((float *)((pd_tensor *)a.val)[k].val)[j] * ((float *)((pd_tensor *)b.val)[j].val)[l];
            ((float *)((pd_tensor *)result.val)[k].val)[l] = sum;
        }
    return (result);
}
*/
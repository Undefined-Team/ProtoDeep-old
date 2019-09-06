#include "pd_main.h"

void        pd_tens_free(pd_tensor tensor)
{
    if (tensor.rank == 0)
        pd_error("The rank of the tensor can't be 0");
    if (tensor.rank > 1)
    {
        for (size_t i = 0; i < tensor.len; i++)
            pd_tens_free(((pd_tensor*)tensor.val)[i]);
    }
    pd_free(tensor.val);
    pd_free(tensor.shape.val);
}
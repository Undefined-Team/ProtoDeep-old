#include "pd_main.h"

static void pd_tens_free_float(pd_tensor *tensor)
{
    if (tensor->rank > 1)
        pd_tens_free_float(((pd_tensor**)tensor->val)[0]);
    else
        pd_free(tensor->val);
}

void        pd_tens_free_new(pd_tensor *tensor)
{
    if (tensor->rank == 0)
        pd_error("The rank of the tensor can't be 0");
    pd_tens_free_float(tensor);
    pd_free(tensor->val);
    pd_arr_free(tensor->shape);
    pd_free(tensor);
}
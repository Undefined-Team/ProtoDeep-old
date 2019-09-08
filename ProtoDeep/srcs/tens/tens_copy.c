#include "pd_main.h"

pd_tensor *pd_tens_copy(pd_tensor *tensor)
{
    pd_tensor *new_tensor;

    new_tensor = pd_tens_new(tensor->rank, tensor->len, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
    if (new_tensor->rank == 1)
    {
        float *a_new_tensor = pd_malloc(sizeof(float) * new_tensor->len);
        new_tensor->val = a_new_tensor;
        float *a_tensor = (float*)tensor->val;
        for (size_t i = 0; i < new_tensor->len; i++)
            a_new_tensor[i] = a_tensor[i];
    }
    else
    {
        pd_tensor **a_new_tensor = pd_malloc(sizeof(pd_tensor*) * new_tensor->len);
        new_tensor->val = a_new_tensor;
        pd_tensor **a_tensor = (pd_tensor**)tensor->val;
        for (size_t i = 0; i < new_tensor->len; i++)
            a_new_tensor[i] = pd_tens_copy(a_tensor[i]);
    }
    new_tensor->shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}
#include "pd_main.h"

void    pd_tens_free(pd_tensor *tensor)
{
    pd_free(tensor->val);
    pd_free(tensor->shape);
    pd_free(tensor->shape_m);
    pd_free(tensor);
}
#include "pd_main.h"

float   *pd_tens_get_first_val(pd_tensor *tensor)
{
    if (tensor->rank > 1)
        return (pd_tens_get_first_val(((pd_tensor **)tensor->val)[0]));
    else
        return ((float *)tensor->val);
}
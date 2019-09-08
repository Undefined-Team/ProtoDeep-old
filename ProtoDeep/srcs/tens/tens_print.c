#include "pd_main.h"

void        pd_tens_print_ctr(pd_tensor *tensor, size_t space)
{
    if (tensor->rank == 0 || tensor->len == 0)
        return ;
    size_t tensor_len = tensor->len;
    if (tensor->rank == 1)
    {
        float *a_tensor = (float*)tensor->val;
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ ", pd_color_t[tensor->rank % PD_COLOR_NBR]);
        for (size_t i = 0; i < tensor_len; i++) printf("%.2f ", a_tensor[i]);
        printf("]%s\n", PD_COLOR_N);
    }
    else
    {
        pd_tensor **a_tensor = (pd_tensor**)tensor->val;
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ %zd%s\n", pd_color_t[tensor->rank % PD_COLOR_NBR], tensor->rank, PD_COLOR_N);
        for (size_t i = 0; i < tensor_len; i++) pd_tens_print_ctr(a_tensor[i], space + 1);
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s]%s\n", pd_color_t[tensor->rank % PD_COLOR_NBR], PD_COLOR_N);
    }
}
#include "pd_main.h"

void        pd_tens_print_ctr(pd_tensor tensor, size_t space)
{
    if (tensor.rank == 0 || tensor.len == 0)
        return ;
    if (tensor.rank == 1)
    {
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ ", pd_color_t[tensor.rank % PD_COLOR_NBR]);
        for (size_t i = 0; i < tensor.len; i++) printf("%.2f ", ((float*)tensor.val)[i]);
        printf("]%s\n", PD_COLOR_N);
    }
    else
    {
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ %zd%s\n", pd_color_t[tensor.rank % PD_COLOR_NBR], tensor.rank, PD_COLOR_N);
        for (size_t i = 0; i < tensor.len; i++) pd_tens_print_ctr((((pd_tensor*)tensor.val))[i], space + 1);
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s]%s\n", pd_color_t[tensor.rank % PD_COLOR_NBR], PD_COLOR_N);
    }
}
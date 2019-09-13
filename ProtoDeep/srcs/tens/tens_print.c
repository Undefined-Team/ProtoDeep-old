#include "pd_main.h"

static void        pd_tens_print_ctr(pd_tensor *tensor, size_t space, size_t *coord)
{
    size_t *shape = tensor->shape;
    size_t rank = tensor->shape_len - space;
    if (rank == 0 || tensor->len == 0)
        return ;
    if (space == tensor->shape_len - 1)
    {
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ ", pd_color_t[rank % PD_COLOR_NBR]);
        for (size_t i = 0; i < shape[space]; i++)
        {
            printf("%.2f ", pd_tens_get_val(tensor, coord));
            ++coord[space];
        }
        printf("]%s\n", PD_COLOR_N);
    }
    else
    {
        pd_tensor **a_tensor = (pd_tensor**)tensor->val;
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ %zd%s\n", pd_color_t[rank % PD_COLOR_NBR], rank, PD_COLOR_N);
        for (size_t i = 0; i < tensor_len; i++)
        {
            pd_tens_print_ctr(a_tensor[i], space + 1, coord);
            ++coord[space];
        }
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s]%s\n", pd_color_t[rank % PD_COLOR_NBR], PD_COLOR_N);
    }
}

void        pd_tens_print(pd_tensor *tensor)
{
    size_t coord[tensor->shape_len] = {0};
    pd_tens_print_ctr(tensor, 0, coord);
}
#include "pd_main.h"

void        pd_arr_print_ctr(pd_arr *array, size_t space)
{
    if (array->len == 0)
        return ;
    if (array->type != PD_T_ARR)
    {
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ ", pd_color_t[space % PD_COLOR_NBR]);
        if (array->type == PD_T_CHAR)
            for (size_t i = 0; i < array->len; i++) printf("'%c'%s ", ((char*)array->val)[i], i != array->len - 1 ? "," : "");
        if (array->type == PD_T_FLOAT)
            for (size_t i = 0; i < array->len; i++) printf("%.2f%s ", ((float*)array->val)[i], i != array->len - 1 ? "," : "");
        if (array->type == PD_T_SIZE_T)
            for (size_t i = 0; i < array->len; i++) printf("%zd%s ", ((size_t*)array->val)[i], i != array->len - 1 ? "," : "");
        if (array->type == PD_T_STDIZ)
            for (size_t i = 0; i < array->len; i++) printf("'stdiz object'%s ", i != array->len - 1 ? "," : "");
        printf("]%s\n", PD_COLOR_N);
    }
    else
    {
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s[ %zd%s\n", pd_color_t[space % PD_COLOR_NBR], space, PD_COLOR_N);
        for (size_t i = 0; i < array->len; i++) pd_arr_print_ctr((((pd_arr **)array->val))[i], space + 1);
        for (size_t i = 0; i < space; i++) printf(PD_PRINT_SPACE);
        printf("%s]%s\n", pd_color_t[space % PD_COLOR_NBR], PD_COLOR_N);
    }
}
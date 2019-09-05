#include "pd_main.h"

pd_float_a   pd_prep_col_to_float(pd_str_a strarr)
{
    pd_float_a newarr;

    newarr = pd_arr_init(PD_T_FLOAT, strarr.len);
    for (size_t i = 0; i < strarr.len; i++)
        ((float*)newarr.val)[i] = pd_math_atof((char*)(((pd_char_a*)strarr.val)[i].val));
    pd_str_free(strarr);
    return newarr;
}

void        pd_prep_all_to_float(pd_csv csv)
{
    for (pd_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == PD_T_STR)
            col->columns = pd_prep_col_to_float(col->columns);
    }
}
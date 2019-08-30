#include "pd_main.h"

t_float_a   prep_col_to_float(t_str_a strarr)
{
    t_float_a newarr;

    newarr = arrInit(T_FLOAT, strarr.len);
    for (size_t i = 0; i < strarr.len; i++)
        ((float*)newarr.val)[i] = math_atof((char*)(((t_char_a*)strarr.val)[i].val));
    strFree(strarr);
    return newarr;
}

void        prep_all_to_float(t_csv csv)
{
    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        if (col->columns.type == T_STR)
            col->columns = prep_col_to_float(col->columns);
    }
}
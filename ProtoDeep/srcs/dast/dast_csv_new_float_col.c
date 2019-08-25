#include "pd_main.h"

t_csv_float_col  *dast_csv_new_float_col(int type, size_t len)
{
    t_csv_float_col *new_fcol;

    PROT_MALLOC(new_fcol = malloc(sizeof(t_csv_float_col)));
    new_fcol->arr = dast_new_farr(len);
    new_fcol->type = type;
    return new_fcol;
}
#include "pd_main.h"

t_csv_float_col  *dast_new_csv_float_col(int type, size_t len)
{
    t_csv_float_col new_ccol;

    PROT_MALLOC(new_ccol = malloc(sieof(t_csv_float_col)));
    new_fcol.arr = dsat_new_farr(len);
    new_fcol.type = type;
    return new_fcol;
}
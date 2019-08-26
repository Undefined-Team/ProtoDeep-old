#include "pd_main.h"

/*t_varr  *dast_init_varr(size_t len, size_t so)
{
    t_varr *new_array;

    PROT_MALLOC(new_array = malloc(sizeof(t_varr)));
    new_array->len = len;
    new_array->arr = malloc(sizeof(so) * len);
    return new_array;
}*/

t_varr  dast_init_varr(size_t len, size_t so)
{
    t_varr new_array;

    //PROT_MALLOC(new_array = malloc(sizeof(t_varr)));
    new_array.len = len;
    new_array.arr = malloc(sizeof(so) * len);
    return new_array;
}
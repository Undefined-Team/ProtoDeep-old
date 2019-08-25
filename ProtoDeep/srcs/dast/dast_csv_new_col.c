#include "pd_main.h"

t_csv_col   *dast_new_col(int type, size_t len, char *name)
{
    t_csv_col   *elem;

    elem->name = name;
    elem->len = len;
    elem->next = NULL;
    if (type == 0)
        elem->columns = dast_new_csv_str_col(len);
    else if (type == 1)
        elem->columns = dsat_new_csv_float_col(len);
    else
        elem->columns = NULL;
    return (elem);
}
#include "pd_main.h"

t_csv_col   *dast_csv_new_col(int type, size_t len, t_carr name)
{
    t_csv_col   *elem = NULL;

    elem->name = name;
    elem->len = len;
    elem->next = NULL;
    if (type == 0)
        elem->columns = dast_csv_new_str_col(type, len);
    else if (type == 1)
        elem->columns = dast_csv_new_float_col(type, len);
    else
        elem->columns = NULL;
    return (elem);
}
#include "pd_main.h"

t_csv_col   dast_new_col(int type, size_t len, char *name)
{
    t_csv_col   *elem;

    elem->type = type;
    elem->name = name;
    elem->len = len;
    elem->columns = NULL;
    return (elem);
}
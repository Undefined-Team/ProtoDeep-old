#include "pd_main.h"

t_csv_col   *dast_csv_new_col(t_arr columns, t_char_a name)
{
    t_csv_col   *elem = NULL;

    PROT_MALLOC(elem = malloc(sizeof(t_csv_col)));
    elem->name = name;
    elem->next = NULL;
    elem->columns = columns;
    return (elem);
}

void    dast_csv_free_col(t_csv_col *elem)
{
    printf("taeme \n");
    arrFree(elem->columns);
    printf("%s %zd %d\n", (char*)elem->name.val, elem->columns.len, elem->columns.type);
    dast_free((void**)&elem);
}
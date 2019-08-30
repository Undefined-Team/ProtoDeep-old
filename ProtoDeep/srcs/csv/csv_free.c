#include "pd_main.h"

void    csv_free(t_csv csv)
{
    t_csv_col *before;

    while (csv.begin)
    {
        before = csv.begin;
        csv.begin = csv.begin->next;
        dast_csv_free_col(before);
    }
}
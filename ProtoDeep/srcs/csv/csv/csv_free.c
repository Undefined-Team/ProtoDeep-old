#include "pd_main.h"

void    pd_csv_free(pd_csv csv)
{
    pd_csv_col *before;

    while (csv.begin)
    {
        before = csv.begin;
        csv.begin = csv.begin->next;
        pd_csv_free_col(before);
    }
}
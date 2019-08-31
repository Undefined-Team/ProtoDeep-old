#include "pd_main.h"

int     prep_csv_split(t_csv csv, t_csv *train, t_csv *test, float f_split)
{
    unsigned int    split;
    t_csv_col       *curr;

    if (f_split > 1)
        f_split = 1;
    else if (f_split < 0)
        f_split = 0;
    split = (unsigned int)((float)csv.height * f_split);
    train->width = csv.width;
    train->height = split;
    train->begin = csv.begin;
    test->width = csv.width;
    test->height = csv.height - split;
    test->begin = (t_csv_col *)malloc(sizeof(t_csv_col));
    curr = test->begin;
    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        curr->name = str_dup(col->name, col->name.len);
        curr->columns = arrInit(T_FLOAT, test->height);
        curr->columns.val = &((float *)col->columns.val)[split];
        // for (size_t i = 0; i <= csv.height - split; i++)
        //     ((float*)curr->columns.val)[i] = ((float*)col->columns.val)[i + split - 1];
        curr->next = col->next ? (t_csv_col *)malloc(sizeof(t_csv_col)) : NULL;
        curr = curr->next;
    }
    return (1);
}
#include "pd_main.h"

int     pd_prep_csv_split(pd_csv csv, pd_csv *train, pd_csv *test, float f_split)
{
    unsigned int    split;
    pd_csv_col       *curr;

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
    test->begin = (pd_csv_col *)pd_malloc(sizeof(pd_csv_col));
    curr = test->begin;
    for (pd_csv_col *col = csv.begin; col; col = col->next)
    {
        curr->name = pd_str_dup(col->name, col->name->len);
        curr->columns = pd_arr_init(PD_T_FLOAT, test->height);
        curr->columns->val = &((float *)col->columns->val)[split];
        curr->next = col->next ? (pd_csv_col *)pd_malloc(sizeof(pd_csv_col)) : NULL;
        curr = curr->next;
    }
    return (1);
}
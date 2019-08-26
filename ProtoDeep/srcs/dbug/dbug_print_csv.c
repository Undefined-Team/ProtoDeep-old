#include "pd_main.h"

size_t  get_str_max_len(t_starr arr)
{
    size_t max = 0;

    for (size_t i = 0; i < arr.len; i++)
    {
        if (arr.arr[i].len > max)
            max = arr.arr[i].len;
    }
    return max;
}

void    dbug_print_csv(t_csv csv)
{
    size_t      col = 0;
    size_t      str_max_len[csv.width];

    for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        if (tmp->type == CSV_STR)
            str_max_len[col] = get_str_max_len(*(t_starr*)tmp->columns);
        else
            str_max_len[col] = 8;
        str_max_len[col] = tmp->name.len > str_max_len[col] ? tmp->name.len : str_max_len[col];
        col++;
    }
    col = 0;
    for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        printf("%*s", (int)str_max_len[col], tmp->name.arr);
        col++;
    }
    printf("\n\n");
    for (size_t line = 0; line < csv.height; line++)
    {
        col = 0;
        for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
        {
            if (tmp->type == CSV_FLOAT)
                printf("% *g", (int)str_max_len[col], ((t_farr*)(tmp->columns))->arr[line]);
            else if (tmp->type == CSV_STR)
                printf ("%*s\n", (int)str_max_len[col], ((t_starr*)(tmp->columns))->arr[line].arr);
            printf(" | ");
            col++;
        }
        printf("\n");
    }
}
#include "pd_main.h"
#include <string.h>

size_t  math_nbr_len(float nbr)
{
    size_t i = 0;

    nbr *= nbr < 0 ? -1 : 1;
    while (nbr >= 1 && ++i)
        nbr /= 10;
    return i < 1 ? 1 : i;
}

size_t utf8len(char *s)
{
    size_t len = 0;
    for (; *s; ++s) if ((*s & 0xC0) != 0x80) ++len;
    return len;
}

size_t  get_str_max_len(t_arr arr)
{
    if (arr.type != T_STR)
        return 0;
    size_t tmp;
    size_t max = 0;
    t_arr *carr = (t_arr*)arr.val;
    for (size_t i = 0; i < arr.len; i++)
    {
        if (carr[i].type != T_CHAR)
            return 0;
        tmp = utf8len((char*)carr[i].val);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

size_t  get_float_max_len(t_arr arr)
{
    if (arr.type != T_FLOAT)
        return 0;
    
    size_t tmp;
    size_t max = 0;
    float *carr = (float*)arr.val;
    for (size_t i = 0; i < arr.len; i++)
    {
        tmp = math_nbr_len(carr[i]);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

void    dbug_print_csv(t_csv csv)
{
    size_t      col = 0;
    size_t      str_max_len[csv.width];
    char        *colors[5] = COLOR_T;

    for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        if (tmp->columns.type == T_STR)
            str_max_len[col] = get_str_max_len(tmp->columns);
        else
            str_max_len[col] = get_float_max_len(tmp->columns) + (2 + DBUG_PREC);
        str_max_len[col] = utf8len((char*)tmp->name.val) > str_max_len[col] ? utf8len((char*)tmp->name.val) : str_max_len[col];
        col++;
    }
    col = 0;
    if (csv.begin)
        printf("| ");
    for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        printf("%s%s%*s%s | ", colors[col % 5], COLOR_U, (int)str_max_len[col], (char*)tmp->name.val, COLOR_N);
        col++;
    }
    printf("\n");
    for (size_t line = 0; line < csv.height; line++)
    {
        if (csv.begin)
            printf("| ");
        col = 0;
        for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
        {
            printf("%s", colors[col % 5]);
            if (tmp->columns.type == T_STR)
            {
                char *strtmp = (char*)(((t_arr*)tmp->columns.val)[line].val);
                size_t pad = str_max_len[col] - utf8len(strtmp);
                printf("%s", strtmp);
                for (size_t i = 0; i < pad; i++)
                    printf(" ");
            }
            else if (tmp->columns.type == T_FLOAT)
            {
                printf("% .*f", DBUG_PREC, ((float*)tmp->columns.val)[line]);
                size_t pad = str_max_len[col] - math_nbr_len(((float*)tmp->columns.val)[line]) - (2 + DBUG_PREC); 
                for (size_t i = 0; i < pad; i++)
                    printf(" ");
            }
            printf("%s | ", COLOR_N);
            col++;
        }
        printf("\n");
    }
    printf("\n");
}
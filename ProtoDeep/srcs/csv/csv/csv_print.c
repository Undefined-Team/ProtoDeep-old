#include "pd_main.h"
char *pd_color_t[PD_COLOR_NBR] = {PD_COLOR_1, PD_COLOR_2, PD_COLOR_3, PD_COLOR_4, PD_COLOR_5};

size_t  pd_math_nbr_len(float nbr)
{
    size_t i = 0;

    nbr *= nbr < 0 ? -1 : 1;
    while (nbr >= 1 && ++i)
        nbr /= 10;
    return i < 1 ? 1 : i;
}

size_t pd_utf8len(char *s)
{
    size_t len = 0;
    for (; *s; ++s) if ((*s & 0xC0) != 0x80) ++len;
    return len;
}

size_t  pd_get_str_max_len(pd_arr arr)
{
    if (arr.type != PD_T_STR)
        return 0;
    size_t tmp;
    size_t max = 0;
    pd_arr *carr = (pd_arr*)arr.val;
    for (size_t i = 0; i < arr.len; i++)
    {
        if (carr[i].type != PD_T_CHAR)
            return 0;
        tmp = pd_utf8len((char*)carr[i].val);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

size_t  pd_get_float_max_len(pd_arr arr)
{
    if (arr.type != PD_T_FLOAT)
        return 0;
    
    size_t tmp;
    size_t max = 0;
    float *carr = (float*)arr.val;
    for (size_t i = 0; i < arr.len; i++)
    {
        tmp = pd_math_nbr_len(carr[i]);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

void    pd_csv_print(pd_csv csv)
{
    size_t      col = 0;
    size_t      str_max_len[csv.width];

    for (pd_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        if (tmp->columns.type == PD_T_STR)
            str_max_len[col] = pd_get_str_max_len(tmp->columns);
        else
            str_max_len[col] = pd_get_float_max_len(tmp->columns) + (2 + PD_DBUG_PREC);
        str_max_len[col] = pd_utf8len((char*)tmp->name.val) > str_max_len[col] ? pd_utf8len((char*)tmp->name.val) : str_max_len[col];
        col++;
    }
    col = 0;
    if (csv.begin)
        printf("| ");
    for (pd_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        printf("%s%s%*s%s | ", pd_color_t[col % PD_COLOR_NBR], PD_COLOR_U, (int)str_max_len[col], (char*)tmp->name.val, PD_COLOR_N);
        col++;
    }
    printf("\n");
    for (size_t line = 0; line < csv.height; line++)
    {
        if (csv.begin)
            printf("| ");
        col = 0;
        for (pd_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
        {
            printf("%s", pd_color_t[col % PD_COLOR_NBR]);
            if (tmp->columns.type == PD_T_STR)
            {
                char *strtmp = (char*)(((pd_arr*)tmp->columns.val)[line].val);
                size_t pad = str_max_len[col] - pd_utf8len(strtmp);
                printf("%s", strtmp);
                for (size_t i = 0; i < pad; i++)
                    printf(" ");
            }
            else if (tmp->columns.type == PD_T_FLOAT)
            {
                printf("% .*f", PD_DBUG_PREC, ((float*)tmp->columns.val)[line]);
                size_t pad = str_max_len[col] - pd_math_nbr_len(((float*)tmp->columns.val)[line]) - (2 + PD_DBUG_PREC); 
                for (size_t i = 0; i < pad; i++)
                    printf(" ");
            }
            printf("%s | ", PD_COLOR_N);
            col++;
        }
        printf("\n");
    }
    printf("\n");
}

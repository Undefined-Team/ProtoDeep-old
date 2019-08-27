#include "pd_main.h"

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
            str_max_len[col] = 8;
        str_max_len[col] = utf8len((char*)tmp->name.val) > str_max_len[col] ? utf8len((char*)tmp->name.val) : str_max_len[col];
        col++;
    }
    col = 0;
    for (t_csv_col *tmp = csv.begin; tmp; tmp = tmp->next)
    {
        printf("%s%s%*s %s| ", colors[col % 5], COLOR_U, (int)str_max_len[col], (char*)tmp->name.val, COLOR_N);
        col++;
    }
    printf("\n");
    for (size_t line = 0; line < csv.height; line++)
    {
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
                printf("% *g", (int)str_max_len[col], ((float*)tmp->columns.val)[line]);
            printf("%s | ", COLOR_N);
            col++;
        }
        printf("\n");
    }
}
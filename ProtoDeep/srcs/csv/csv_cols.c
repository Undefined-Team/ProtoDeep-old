#include "pd_main.h"

t_csv_col   *csv_add_col(t_char_a name, size_t height)
{
    t_csv_col   *col;

    col = (t_csv_col *)malloc(sizeof(t_csv_col));
    col->name = name;
    col->next = NULL;
    col->columns = arrInit(T_ARR, height);
    return (col);
}

t_csv_col   *csv_init_cols(t_tokens_list *line, int header, size_t width, size_t height)
{
    t_csv_col       *col_list = NULL;
    t_csv_col       *col = NULL;

    if (line)
        line = line;
    if (header)
    {
        for (size_t i = 0; i < width; i++)
        {
            t_char_a name = (t_char_a)((t_str_a *)line->tokens.val)[i];
            if ((!col_list && !(col_list = csv_add_col(name, height)))
                || (col && !(col->next = csv_add_col(name, height))))
                return (NULL);
            col = col ? col->next : col_list;
        }
    }
    else
    {
        for (size_t i = 0; i < width; i++)
        {
            if ((!col_list && !(col_list = csv_add_col(str_join(strSNew("c"), math_itoa(i)), height)))
                || (col && !(col->next = csv_add_col(str_join(strSNew("c"), math_itoa(i)), height))))
                return (NULL);
            col = col ? col->next : col_list;
        }
    }
    return (col_list);
}

t_csv_col   *create_cols(t_tokens_list *tokens, int header, size_t width, size_t height)
{
    t_tokens_list   *line = tokens;
    t_csv_col       *col_list = NULL;
    t_csv_col       *col = NULL;

    col_list = csv_init_cols(line, header, width, height - header);
    line = header ? line->next : tokens;
    for (size_t i = 0; i < height - header; i++)
    {
        col = col_list;
        for (size_t j = 0; j < width; j++)
        {
            if (line->tokens.len)
                ((t_str_a *)col->columns.val)[i] = (t_char_a)((t_str_a *)line->tokens.val)[j];
            else
                ((t_str_a *)col->columns.val)[i] = arrInit(T_CHAR, 0);
            col = col->next;
        }
        line = line->next;
    }
    if (tokens)
        csv_free_tokens_list(tokens);
    return (col_list);
}
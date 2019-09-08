#include "pd_main.h"

pd_csv_col   *pd_csv_add_col(pd_char_a *name, size_t height)
{
    pd_csv_col   *col;

    col = (pd_csv_col *)pd_malloc(sizeof(pd_csv_col));
    col->name = name;
    col->next = NULL;
    col->columns = pd_arr_init(PD_T_ARR, height);
    return (col);
}

pd_csv_col   *pd_csv_init_cols(pd_tokens_list *line, int header, size_t width, size_t height)
{
    pd_csv_col       *col_list = NULL;
    pd_csv_col       *col = NULL;

    if (line)
        line = line;
    if (header)
    {
        pd_str_a **t_line_tokens_val = (pd_str_a **)line->tokens->val;
        for (size_t i = 0; i < width; i++)
        {
            pd_char_a *name = (pd_char_a *)t_line_tokens_val[i];
            if ((!col_list && !(col_list = pd_csv_add_col(name, height)))
                || (col && !(col->next = pd_csv_add_col(name, height))))
                return (NULL);
            col = col ? col->next : col_list;
        }
    }
    else
    {
        for (size_t i = 0; i < width; i++)
        {
            if ((!col_list && !(col_list = pd_csv_add_col(pd_str_join(pd_str_new_s("c"),pd_math_itoa(i)), height)))
                || (col && !(col->next = pd_csv_add_col(pd_str_join(pd_str_new_s("c"), pd_math_itoa(i)), height))))
                return (NULL);
            col = col ? col->next : col_list;
        }
    }
    return (col_list);
}

pd_csv_col   *pd_csv_create_cols(pd_tokens_list *tokens, int header, size_t width, size_t height)
{
    pd_tokens_list   *line = tokens;
    pd_csv_col       *col_list = NULL;
    pd_csv_col       *col = NULL;

    col_list = pd_csv_init_cols(line, header, width, height - header);
    line = header ? line->next : tokens;
    for (size_t i = 0; i < height - header; i++)
    {
        col = col_list;
        pd_str_a **t_col_columns_val = (pd_str_a **)col->columns->val;
        pd_str_a **t_line_tokens_val = (pd_str_a **)line->tokens->val;
        for (size_t j = 0; j < width; j++)
        {
            if (line->tokens->len)
                t_col_columns_val[i] = (pd_char_a *)t_line_tokens_val[j];
            else
                t_col_columns_val[i] = pd_arr_init(PD_T_CHAR, 0);
            col = col->next;
        }
        line = line->next;
    }
    if (tokens)
        pd_csv_free_tokens_list(tokens);
    return (col_list);
}

pd_csv_col   *pd_csv_new_col(pd_arr *columns, pd_char_a *name)
{
    pd_csv_col   *elem = NULL;

    PD_PROT_MALLOC(elem = pd_malloc(sizeof(pd_csv_col)));
    elem->name = name;
    elem->next = NULL;
    elem->columns = columns;
    return (elem);
}

void    pd_csv_free_col(pd_csv_col *elem)
{
    pd_arr_free_r(elem->columns, -1);
    pd_str_free(elem->name);
    pd_free(elem);
}
#include "pd_main.h"
# define BUF_SIZE 1000

t_char_a retrieve_line(t_char_a *content)
{
    t_char_a     line;
    size_t      len;

    if ((len = str_chr(*content, '\n')))
    {
        line = str_dup(*content, len);
        *content = str_sub(*content, len, content->len);
    }
    else
    {
        len = str_len(*content);
        line = str_dup(*content, len);
        *content = str_sub(*content, len, content->len);
    }
    return (line);
}

int     csv_get_line(int fd, t_char_a *line)
{
    t_char_a             buf;
    size_t              ret;
    static t_char_a      content;

    buf = arrInit(T_CHAR, 64);
    if (fd < 0 || line->val == NULL || read(fd, buf.val, 0) < 0)
        return (-1);
    if (!content.val)
        content = arrInit(T_CHAR, 0);
    while ((ret = read(fd, buf.val, 64)))
    {
        ((char *)buf.val)[ret] = '\0';
        content = str_join(content, buf);
        if (!content.val)
            return (-1);
        if (str_chr(content, '\n'))
            break;
    }
    if (ret < 64 && !str_len(content))
        return (0);
    *line = retrieve_line(&(content));
    if (!line->val)
        return (-1);
    return (1);
}

t_tokens_list   *add_tokens(t_arr tokens)
{
    t_tokens_list   *elem;

    elem = (t_tokens_list *)malloc(sizeof(t_tokens_list));
    elem->tokens = tokens;
    elem->next = NULL;
    return (elem);
}

t_tokens_list   *create_tokens_list(int fd, size_t *height, size_t *width)
{
    t_arr           *line = NULL;
    t_tokens_list   *list = NULL;
    t_tokens_list   *curr = NULL;
    t_arr           tokens;

    line = (t_arr *)malloc(sizeof(t_arr));
    *line = arrInit(T_CHAR, 0);
    ((char *)line->val)[0] = 0;
    while (csv_get_line(fd, line))
    {
        tokens = str_split(*line, ',');
        if ((!list && !(list = add_tokens(tokens)))
            || (curr && !(curr->next = add_tokens(tokens))))
            return (NULL);
        curr = curr ? curr->next : list;
        *height = *height + 1;
    }
    *width = tokens.len;
    return (list);
}

t_csv       *init_csv(t_csv_col *array, int header, size_t width, size_t height)
{
    t_csv   *csv;

    csv = (t_csv *)malloc(sizeof(t_csv));
    csv->begin = array;
    csv->width = width;
    csv->height = height - header;
    return (csv);
}

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

    if (header)
    {
        for (size_t i = 0; i < width; i++)
        {
            t_char_a name = str_dup(((t_arr *)(line->tokens.val))[i], ((t_arr *)(line->tokens.val))[i].len);
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
            //ajouter nom de col : c1, c2, c3..., cn
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
                ((t_arr *)col->columns.val)[i] = ((t_arr *)line->tokens.val)[j];
            else
                ((t_arr *)col->columns.val)[i] = arrInit(T_CHAR, 0);
            col = col->next;
        }
        line = line->next;
    }
    return (col_list);
}

t_csv   *csv_read(char *file_name, int header)
{
    int             fd = open(file_name, O_RDONLY);
    t_csv           *csv;
    t_csv_col       *array = NULL;
    t_tokens_list   *tokens_list;
    size_t          height = 0;
    size_t          width = 0;

    tokens_list = create_tokens_list(fd, &height, &width);
    array = create_cols(tokens_list, header, width, height);
    csv = init_csv(array, header, width, height);
    return (csv);
}
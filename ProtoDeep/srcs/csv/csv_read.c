#include "pd_main.h"
# define BUF_SIZE 1000

typedef struct      s_file
{
    int             fd;
    t_arr           content;
    t_arr           content_start;
}                   t_file;

t_str_a retrieve_line(t_str_a *content)
{
    t_str_a     line;
    size_t      len;

    if ((len = str_chr(*content, '\n')))
    {
        line = str_dup(*content, len);
        ((char *)line.val)[line.len - 1] = 0;
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

int     csv_get_line(int fd, t_str_a *line)
{
    t_str_a             buf;
    size_t              ret;
    static t_str_a      content;

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

t_tokens_list   *create_tokens_list(int fd, int header, int *count)
{
    t_arr           *line = NULL;
    t_tokens_list   *list = NULL;
    t_tokens_list   *curr = NULL;
    t_arr           tokens;

    if (header)
        header = 0;
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
        *count = *count + 1;
    }
    return (list);
}

t_csv_col   *csv_read(char *file_name, int header)
{
    int             fd = open(file_name, O_RDONLY);
    t_csv_col       *array = NULL;
    t_tokens_list   *tokens_list;
    int             count = 0;

    tokens_list = create_tokens_list(fd, header, &count);
    while (tokens_list)
    {
        if (tokens_list->tokens.val)
        {
            printf("%zd\n", tokens_list->tokens.len);
            for (size_t i = 0; i < tokens_list->tokens.len; i++)
            {
                printf("%s\n", ((char *)((t_arr *)(tokens_list->tokens.val))[i].val) );
            }
        }
        tokens_list = tokens_list->next;
    }
    return (array);
}
#include "pd_main.h"

void        csv_free_tokens_list(t_tokens_list *tokens)
{
    t_tokens_list   *curr;

    if (!tokens->next)
        free(tokens);
    else
    {
        curr = tokens->next;
        while (tokens)
        {
            free(tokens);
            tokens = curr;
            if (curr)
                curr = curr->next;
        }
    }
}

t_char_a csv_retrieve_line(t_char_a *content)
{
    t_char_a     line;
    size_t      len;

    if ((len = str_chr(*content, '\n')))
    {
        line = str_dup(*content, len - 2);
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
    {
        return (0);
    }
    *line = csv_retrieve_line(&(content));
    if (!line->val)
        return (-1);
    return (1);
}

t_tokens_list   *csv_add_tokens(t_arr tokens)
{
    t_tokens_list   *elem;

    elem = (t_tokens_list *)malloc(sizeof(t_tokens_list));
    elem->tokens = tokens;
    elem->next = NULL;
    return (elem);
}

t_tokens_list   *csv_create_tokens_list(int fd, size_t *height, size_t *width)
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
        if ((!list && !(list = csv_add_tokens(tokens)))
            || (curr && !(curr->next = csv_add_tokens(tokens))))
            return (NULL);
        curr = curr ? curr->next : list;
        *height = *height + 1;
    }
    *width = tokens.len;
    close(fd);
    curr = list;
    return (list);
}
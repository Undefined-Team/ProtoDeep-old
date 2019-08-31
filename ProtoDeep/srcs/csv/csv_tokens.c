#include "pd_main.h"

void        csv_free_tokens_list(t_tokens_list *tokens)
{
    t_tokens_list   *curr;

    if (!tokens->next)
	{
		free(tokens->tokens.val);
        free(tokens);
    }
	else
    {
        curr = tokens->next;
        while (tokens)
        {
			free(tokens->tokens.val);
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

	if (line.val)
		free(line.val);
    if ((len = str_chr(*content, '\n')))
    {
       line = str_dup(*content, len - 2);
        *content = str_fsub(*content, len, content->len);
    }
    else
    {
        len = str_len(*content);
        line = str_dup(*content, len);
        *content = str_fsub(*content, len, content->len);
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
        content = str_fjoin(content, str_dup(buf, buf.len));
        if (!content.val)
            return (-1);
        if (str_chr(content, '\n'))
            break;
    }
	free(buf.val);
    if (ret < 64 && !str_len(content))
    {
		free(content.val);
		content.val = NULL;
        return (0);
    }
	free(line->val);
	line->val = NULL;
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

t_tokens_list   *csv_wrong_width(size_t i, size_t first_width, size_t width)
{
    write(2, "read_csv error: ", 16);
    if (first_width > width)
        write(2, "Not enough values on line ", 26);
    else if (first_width < width)
        write(2, "Too much values on line ", 24);
    t_arr line = math_itoa(i + 1);
    write(2, (char *)line.val, line.len);
    write(2, ".\n", 2);
    return (NULL);
}

t_tokens_list   *csv_create_tokens_list(int fd, char separator, size_t *height, size_t *width)
{
    t_arr           *line = NULL;
    t_tokens_list   *list = NULL;
    t_tokens_list   *curr = NULL;
    t_arr           tokens;
    size_t          first_width = 0;

    line = (t_arr *)malloc(sizeof(t_arr));
    *line = arrInit(T_CHAR, 0);
    ((char *)line->val)[0] = 0;
    while (csv_get_line(fd, line))
    {
        if (!line || line->len == 0)
            continue;
        tokens = str_split(*line, separator, 1);
        if (tokens.len == 0)
            continue;
        if ((!first_width && !(first_width = tokens.len)) || (first_width != tokens.len))
            return (csv_wrong_width(*height, first_width, tokens.len));
        if ((!list && !(list = csv_add_tokens(tokens)))
            || (curr && !(curr->next = csv_add_tokens(tokens))))
            return (NULL);
        curr = curr ? curr->next : list;
        *height = *height + 1;
    }
    *width = first_width;
	free(line->val);
	free(line);
    close(fd);
    return (list);
}

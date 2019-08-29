#include "pd_main.h"

typedef struct  s_split_list
{
    t_arr              word;
    struct s_split_list *next;
}               t_split_list;

static t_split_list    *add_elem(t_arr word)
{
    t_split_list    *new;

    new = (t_split_list *)malloc(sizeof(t_split_list));
    new->word = arrInit(T_CHAR, 0);
    new->word = str_whitespace(word);
    new->word.len = str_len(new->word);
    new->next = NULL;
    return (new);
}

static t_split_list    *count_sep(t_arr str, char sep)
{
    int             i = -1;
    int             j = 0;
    size_t          count = 0;
    t_split_list    *token_sizes;
    t_split_list    *curr;

    token_sizes = NULL;
    curr = NULL;
    str = str_whitespace(str);
    while (++i >= 0)
    {
        if (((char *)str.val)[i] == sep || ((char *)str.val)[i] == '\0')
        {
            if ((!token_sizes && !(token_sizes = add_elem(str_sub(str, j, i - j))))
                || (curr && !(curr->next = add_elem(str_sub(str, j, i - j)))))
                return (NULL);
            curr = curr ? curr->next : token_sizes;
            count++;
            j = i + 1;
            if (((char *)str.val)[i] == '\0')
                break;
        }
    }
    return (token_sizes);
}

t_arr     str_split(t_arr str, char sep)
{
    t_split_list    *words;
    t_split_list    *curr;
    size_t          count = 0;
    t_arr         tokens;

    words = count_sep(str, sep);
    curr = words;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    if (!count)
        return (tokens);
    tokens = arrInit(T_STR, count);
    tokens.len = count;
    count = 0;
    curr = words;
    while (curr)
    {
        ((t_arr *)tokens.val)[count++] = str_dup(curr->word, curr->word.len);
        curr = curr->next;
    }
    return (tokens);
}
#include "pd_main.h"

typedef struct  s_split_list
{
    char                *word;
    struct s_split_list *next;
}               t_split_list;

static t_split_list    *add_elem(char *word)
{
    t_split_list    *new;

    new = (t_split_list *)malloc(sizeof(t_split_list));
    new->word = str_whitespace(word);
    new->next = NULL;
    return (new);
}

static t_split_list    *count_sep(char *str, char sep)
{
    int             i = -1;
    int             j = 0;
    size_t          count = 0;
    t_split_list    *token_sizes;
    t_split_list    *curr;

    token_sizes = NULL;
    curr = NULL;
    while (str[++i])
    {
        if (str[i] == sep && str[i + 1] != 0)
        {
            if ((!token_sizes && !(token_sizes = add_elem(str_sub(str, j, i - j))))
                || (curr && !(curr->next = add_elem(str_sub(str, j, i - j)))))
                return (NULL);
            curr = curr ? curr->next : token_sizes;
            count++;
            j = i + 1;
        }
    }
    return (token_sizes);
}

char    **str_split(char *str, char sep)
{
    t_split_list    *words;
    t_split_list    *curr;
    size_t          count = 0;
    char            **tokens;

    words = count_sep(str, sep);
    curr = words;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    if (!count)
        return (NULL);
    tokens = (char **)malloc((count + 1) * sizeof(char *));
    tokens[count] = NULL;
    count = 0;
    curr = words;
    while (curr)
    {
        tokens[count++] = str_dup(curr->word);
        curr = curr->next;
    }
    return (tokens);
}
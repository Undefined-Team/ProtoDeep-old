#include "pd_main.h"

static void				pd_free_word(pd_arr new_word, pd_arr word, pd_arr escape, pd_arr white_space)
{
	if (word.val != new_word.val)
		pd_free(word.val);
	if (white_space.val != new_word.val)
		pd_free(white_space.val);
	if (escape.val != new_word.val)
		pd_free(escape.val);
}

static pd_split_list    *pd_add_elem(pd_arr word)
{
    pd_split_list    *new;
	pd_arr			white_space;
	pd_arr			escape;

	white_space = pd_str_whitespace(word);
	escape = pd_str_escape(white_space);
    new = (pd_split_list *)pd_malloc(sizeof(pd_split_list));
    new->word = escape;
	pd_free_word(new->word, word, escape, white_space);
    new->word.len = pd_str_len(new->word);
    new->next = NULL;
    return (new);
}

static pd_split_list    *pd_count_sep(pd_arr str, char sep, int escape)
{
    size_t          i = 0;
    size_t          j = 0;
    size_t          count = 0;
    pd_split_list    *token_sizes;
    pd_split_list    *curr;
    int             d_escaped = 0;
    int             escaped = 0;

    token_sizes = NULL;
    curr = NULL;
    str = pd_str_whitespace(str);
    while (1)
    {
        if (escape)
        {
            if (((char *)str.val)[i] == '\"')
                d_escaped = !d_escaped;
            else if (((char *)str.val)[i] == '\'')
                escaped = !escaped;
        }
        if (escaped || d_escaped)
        {
            if (((char *)str.val)[i] == '\0')
                return (NULL);
            i++;
            continue;
        }
        if (((char *)str.val)[i] == sep || ((char *)str.val)[i] == '\0')
        {
            pd_arr sub = i - j > 0 ? pd_str_sub(str, j, i - j) : pd_arr_init(PD_T_CHAR, 0);
            if ((!token_sizes && !(token_sizes = pd_add_elem(sub)))
                || (curr && !(curr->next = pd_add_elem(sub))))
                return (NULL);
            curr = curr ? curr->next : token_sizes;
            count++;
            j = i + 1;
            if (((char *)str.val)[i] == '\0')
                break;
        }
        i++;
    }
	free(str.val);
    return (token_sizes);
}

pd_arr     pd_str_split(pd_arr str, char sep, int escape)
{
    pd_split_list   *words;
    pd_split_list   *curr;
    size_t          count = 0;
    pd_arr          tokens;

    if (!(words = pd_count_sep(str, sep, escape)))
        return (pd_arr_init(PD_T_STR, 0));
    curr = words;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    if (!count)
        return (tokens);
    tokens = pd_arr_init(PD_T_STR, count);
    tokens.len = count;
    count = 0;
    curr = words;
    while (curr)
    {
        ((pd_arr *)tokens.val)[count++] = pd_str_dup(curr->word, curr->word.len);
		pd_free(curr->word.val);
        pd_split_list *tmp = curr;
		curr = curr->next;
		pd_free(tmp);
    }
    return (tokens);
}

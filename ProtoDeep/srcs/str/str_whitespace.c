#include "pd_main.h"

static int     pd_is_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\0')
        return (1);
    return (0);
}

pd_arr  pd_str_whitespace(pd_arr str)
{
    int     i = 0;
    int     j = pd_str_len(str) - 1;

    if (!str.val || str.len == 0)
        return (str);
    while (pd_is_whitespace(((char *)str.val)[i]))
        i++;
    while (pd_is_whitespace(((char *)str.val)[j]))
        j--;
    return (pd_str_sub(str, i, j - i + 1));
}
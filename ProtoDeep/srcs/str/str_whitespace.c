#include "pd_main.h"

static int     is_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}

char    *str_whitespace(char *str)
{
    int     i = 0;
    int     j = str_len(str) - 1;

    while (is_whitespace(str[i]))
        i++;
    while (is_whitespace(str[j]))
        j--;
    return (str_sub(str, i, j - i + 1));
}
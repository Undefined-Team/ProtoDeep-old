#include "pd_main.h"

static int     is_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\0')
        return (1);
    return (0);
}

t_arr  str_whitespace(t_arr str)
{
    int     i = 0;
    int     j = str_len(str) - 1;

    // printf(">> [%s]\n", (char *)str.val);
    while (is_whitespace(((char *)str.val)[i]))
        i++;
    while (is_whitespace(((char *)str.val)[j]))
        j--;
    // printf("<< [%s]\n", (char *)str_sub(str, i, j - i + 1).val);
    return (str_sub(str, i, j - i + 1));
}
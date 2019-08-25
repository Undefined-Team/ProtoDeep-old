#include "pd_main.h"

static int     is_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}

t_carr  str_whitespace(t_carr str)
{
    int     i = 0;
    int     j = str.len - 1;

    while (is_whitespace(str.arr[i]))
        i++;
    while (is_whitespace(str.arr[j]))
        j--;
    return (str_sub(str, i, j - i + 1));
}
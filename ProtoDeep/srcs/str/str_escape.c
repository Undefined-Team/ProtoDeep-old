#include "pd_main.h"

t_arr  str_escape(t_arr str)
{
    int     i = 0;
    int     j = str_len(str) - 1;

    if (!str.val || str.len == 0)
        return (str);
    if (((char *)str.val)[i] == '\"' && ((char *)str.val)[j] == '\"')
        return (str_sub(str, i + 1, j - 1));
    if (((char *)str.val)[i] == '\'' && ((char *)str.val)[j] == '\'')
        return (str_sub(str, i + 1, j - 1));
    return (str);
}
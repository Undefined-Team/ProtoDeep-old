#include "pd_main.h"

pd_arr  pd_str_escape(pd_arr str)
{
    int     i = 0;
    int     j = pd_str_len(str) - 1;

    if (!str.val || str.len == 0)
        return (str);
    if (((char *)str.val)[i] == '\"' && ((char *)str.val)[j] == '\"')
        return (pd_str_sub(str, i + 1, j - 1));
    if (((char *)str.val)[i] == '\'' && ((char *)str.val)[j] == '\'')
        return (pd_str_sub(str, i + 1, j - 1));
    return (str);
}
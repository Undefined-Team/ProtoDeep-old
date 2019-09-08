#include "pd_main.h"

int     pd_str_chr(pd_arr str, char c)
{
    char *a_str = (char*)str.val;
    for (size_t i = 0; a_str[i]; i++)
        if (a_str[i] == c)
            return (i + 1);
    return (0);
}
#include "pd_main.h"

char    *str_dup(char *str)
{
    size_t  len;
    char    *dup;
    size_t  i;

    if (!str)
        return (NULL);
    len = str_len(str);
    dup = (char *)malloc(len + 1);
    i = -1;
    while (++i < len)
        dup[i] = str[i];
    dup[i] = 0;
    return (dup);
}
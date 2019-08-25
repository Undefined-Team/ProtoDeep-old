#include "pd_main.h"

char    *str_sub(char *str, size_t start, size_t length)
{
    size_t  len = str_len(str);
    char    *sub;

    if (start > len)
        return (NULL);
    sub = str_dup(&str[start]);
    if (length > len)
        return (sub);
    sub[length] = 0;
    return (sub);
}
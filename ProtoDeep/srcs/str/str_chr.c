#include "pd_main.h"

int     pd_str_chr(pd_arr str, char c)
{
    for (size_t i = 0; ((char *)str.val)[i]; i++)
        if (((char *)str.val)[i] == c)
            return (i + 1);
    return (0);
}
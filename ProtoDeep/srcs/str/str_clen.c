#include "pd_main.h"

size_t  pd_str_clen(char* str)
{
    if (!str)
        return 0;
    
    size_t  i = 0;

    while (str[i])
        i++;
    return (i);
}
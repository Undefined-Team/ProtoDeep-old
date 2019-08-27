#include "pd_main.h"

size_t  str_len(char* str)
{
    if (!str)
        return 0;
    
    size_t  i = 0;

    while (str[i])
        i++;
    return (i);
}
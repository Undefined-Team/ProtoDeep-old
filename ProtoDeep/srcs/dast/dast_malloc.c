#include "pd_main.h"

void    *pd_dast_malloc(size_t len)
{
    if (len > 0)
    {
            void *tmp = malloc(len);
            if (tmp)
                    return tmp;
            pd_error("Too much memory allocated (%zd bytes).", len);
    }
    return NULL;
}

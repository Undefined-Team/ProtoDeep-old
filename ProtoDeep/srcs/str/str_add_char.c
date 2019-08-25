#include "pd_main.h"

t_carr    str_add_char(t_carr str, char c)
{
    char *new_strc;

    if (!(new_strc = malloc(sizeof(char) * str.len + 2)))
        return dast_new_static_carr("", 0);
    for (size_t i = 0; i < str.len; i++)
        new_strc[i] = str.arr[i];
    dast_free((void*)str.arr);
    new_strc[str.len] = c;
    new_strc[str.len + 1] = 0;
    return dast_new_carr(new_strc, str.len + 1);
}
#include "pd_main.h"

t_carr  str_char_to_str(char c)
{
    char *new_strc;

    if (!(new_strc = malloc(sizeof(char) + 1)))
        return dast_new_static_carr("", 0);
    new_strc[0] = c;
    new_strc[1] = 0;
    return dast_new_carr(new_strc, 1);
}
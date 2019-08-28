#include "pd_main.h"

t_char_a  str_char_to_str(char c)
{
    char *new_strc;

    if (!(new_strc = malloc(sizeof(char) * 2)))
        return strSNew("");
    new_strc[0] = c;
    new_strc[1] = '\0';
    return strNew(new_strc);
}
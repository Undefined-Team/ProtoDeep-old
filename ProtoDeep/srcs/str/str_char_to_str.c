#include "pd_main.h"

pd_char_a  pd_str_char_to_str(char c)
{
    char *new_strc;

    if (!(new_strc = malloc(sizeof(char) * 2)))
        return pd_strSNew("");
    new_strc[0] = c;
    new_strc[1] = '\0';
    return pd_strNew(new_strc);
}
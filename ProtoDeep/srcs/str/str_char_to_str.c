#include "pd_main.h"

pd_char_a  pd_str_char_to_str(char c)
{
    char *new_strc;

    if (!(new_strc = pd_malloc(sizeof(char) * 2)))
        return pd_str_new_s("");
    new_strc[0] = c;
    new_strc[1] = '\0';
    return pd_str_new(new_strc);
}
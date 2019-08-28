#include "pd_main.h"

t_char_a  str_char_to_str(char c)
{
    char *new_strc;

    printf("PUTE2 |%c|\n", c);
    if (!(new_strc = malloc(sizeof(char) * 2)))
    {
        //printf("PUTE3\n");
        return strSNew("");
    }
    //printf("PUTE4\n");
    new_strc[0] = c;
    new_strc[1] = '\0';
    //printf("PUTE\n");
    return strNew(new_strc);
}
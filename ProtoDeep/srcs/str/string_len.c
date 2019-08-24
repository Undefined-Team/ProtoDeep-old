#include "pd_main.h"

unsigned long   str_len(char *str)
{
    int i = 0;

    while (str)
    {
        if (!str[i])
            return (i);
        else if (!str[i + 1])
            return (i + 1);
        else if (!str[i + 2])
            return (i + 2);
        else if (!str[i + 3])
            return (i + 3);
        else if (!str[i + 4])
            return (i + 4);
        else if (!str[i + 5])
            return (i + 5);
        else if (!str[i + 6])
            return (i + 6);
        else if (!str[i + 7])
            return (i + 7);
        else if (!str[i + 8])
            return (i + 8);
        else if (!str[i + 9])
            return (i + 9);
        else if (!str[i + 10])
            return (i + 10);
        else if (!str[i + 11])
            return (i + 11);
        else if (!str[i + 12])
            return (i + 12);
        else if (!str[i + 13])
            return (i + 13);
        else if (!str[i + 14])
            return (i + 14);
        else if (!str[i + 15])
            return (i + 15);
        i += 16;
    }
    return (-1);
}
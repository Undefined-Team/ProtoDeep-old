#include "pd_main.h"
#include <string.h>

int main(int ac, char **av)
{
    if (!ac)
        return (0);
    int i = -1;
    while (++i < 100000)
        printf("%lu\n", string_len(av[1]));
    return (0);
}
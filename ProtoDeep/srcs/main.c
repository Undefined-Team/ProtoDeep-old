#include "pd_math.h"

int main(int ac, char **av)
{
    if (ac)
        printf("%f\n", math_pow(atof(av[1]), atof(av[2])));
    return (0);
}
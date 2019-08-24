#include "pd_main.h"

/*int main(int ac, char **av)
{
    //if (ac)
    //    printf("%f\n", math_pow(atof(av[1]), atof(av[2])));

    //float test[5] = {0.1, -1.5, 5.5, 100, -16.6};

    printf("segfault\n");

    //printf("max = %f\n", math_max_a(test, 5));
    return (0);
}*/

int main(void)
{
    printf("helo world\n");
    float test[5] = {0.1, -1.5, 5.5, 100, -16.6};
    //float test2[0];
    printf("segfault\n");

    printf("max = %f\n", math_max_a(test, 5));
    printf("min = %f\n", math_min_a(test, 5));
    printf("atof = %f\n", math_atof("0.111111"));

    float *test2 = prep_stdiz(test, 5);
    for (size_t i = 0; i < 5; i++)
    {
        printf("--> %f\n", test2[i]);
    }
    return (0);
}
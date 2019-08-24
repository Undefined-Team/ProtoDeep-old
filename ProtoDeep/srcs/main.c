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
    float train_set[5] = {0.1, -1.5, 5.5, 100, -16.6};
    float test_set[5] = {0.1, -1.5, 5.5, -100, -16.6};
    //float test2[0];
    printf("segfault\n");

    printf("max = %f\n", math_max_a(train_set, 5));
    printf("min = %f\n", math_min_a(train_set, 5));
    printf("atof = %f\n", math_atof("0.111111"));

    t_prep_data pdata;
    float *test3 = prep_stdiz_init(train_set, 5, &pdata);
    printf("On standardise le train_set avec mean = %f et std_dev = %f et min = %f et maxsmin = %f\n", pdata.mean, pdata.std_dev, pdata.min, pdata.maxsmin);
    for (size_t i = 0; i < 5; i++)
    {
        printf("--> %f\n", test3[i]);
    }
    printf("\nOn standardise le test_set par rapport à la standardisation du train_set\n");
    float *test4 = prep_stdiz(test_set, 5, pdata);
    for (size_t i = 0; i < 5; i++)
    {
        printf("--> %f\n", test4[i]);
    }
    return (0);
}
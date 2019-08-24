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
    float t1[5] = {0.1, -1.5, 5.5, 100, -16.6};
    float t2[5] = {0.1, -1.5, 5.5, -100, -16.6};
    t_farr train_set = dast_new_farr(5);
    t_farr test_set = dast_new_farr(5);

    train_set.arr = t1;
    test_set.arr = t2;
    //float test2[0];
    printf("segfault\n");

    printf("max = %f\n", math_max_a(train_set));
    printf("min = %f\n", math_min_a(train_set));
    printf("atof = %f\n", math_atof("0.111111"));

    t_prep_data pdata;
    t_farr test3 = prep_stdiz_init(train_set, &pdata);
    printf("On standardise le train_set avec mean = %f et std_dev = %f et min = %f et maxsmin = %f\n", pdata.mean, pdata.std_dev, pdata.min, pdata.maxsmin);
    for (size_t i = 0; i < test3.len; i++)
    {
        printf("--> %f\n", test3.arr[i]);
    }
    printf("\nOn standardise le test_set par rapport à la standardisation du train_set\n");
    t_farr test4 = prep_stdiz(test_set, pdata);
    for (size_t i = 0; i < test4.len; i++)
    {
        printf("--> %f\n", test4.arr[i]);
    }
    return (0);
}
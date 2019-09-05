#include "pd_main.h"
//size_t jsp = 0;
#include <string.h>

/*void     pd_error(...)
{
    fprintf(stderr, PD_COLOR_3);
    fprintf(stderr, __VA_ARGS__);
    fprintf(stderr, "%s\n", PD_COLOR_N);
    exit(1);
}*/

pd_csv   pd_get_test_csv_1(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_char_a col3[4] = {pd_strSNew("Gros"), pd_strSNew("Pitit"), pd_strSNew("Moyen"), pd_strSNew("Moyen")};
    tmp = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col3), pd_strSNew("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_FLOAT, 4, col1), pd_strSNew("Qi"));
    tmp = tmp->next;

    pd_char_a col2[4] = {pd_strSNew("Timothée"), pd_strSNew("Sylvain"), pd_strSNew("Paco"), pd_strSNew("Tony")};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col2), pd_strSNew("Name"));
    tmp = tmp->next;

    pd_char_a col4[4] = {pd_strSNew("Ca va"), pd_strSNew("Musclée"), pd_strSNew("Musclée"), pd_strSNew("Musclée")};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col4), pd_strSNew("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

pd_csv   pd_get_test_csv_2(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_char_a col3[4] = {pd_strSNew("Gros"), pd_strSNew("Pitit"), pd_strSNew("JSP"), pd_strSNew("Moyen")};
    tmp = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col3), pd_strSNew("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_FLOAT, 4, col1), pd_strSNew("Qi"));
    tmp = tmp->next;

    pd_char_a col2[4] = {pd_strSNew("Timothée"), pd_strSNew("Sylvain"), pd_strSNew("Paco"), pd_strSNew("Tony")};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col2), pd_strSNew("Name"));
    tmp = tmp->next;

    pd_char_a col4[4] = {pd_strSNew("Ca va"), pd_strSNew("Musclée"), pd_strSNew("Musclée"), pd_strSNew("JSP")};
    tmp->next = pd_csv_new_col(pd_arrSNew(PD_T_STR, 4, col4), pd_strSNew("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

void    pd_csv_with_conf()
{
    pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
    //pd_csv csv_1 = get_test_csv_1();
    pd_csv_print(csv_1);

    pd_char_a del_1[1] = {pd_strSNew("Name")};
    pd_char_a ohe_1[2] = {pd_strSNew("Main droite"), pd_strSNew("Zizi")};
    pd_csv_conf conf = pd_prep_init_conf(pd_arrSNew(PD_T_STR, 1, del_1), pd_arrSNew(PD_T_STR, 2, ohe_1));
    pd_prep_prepare(&csv_1, &conf);
    pd_csv_print(csv_1);

    pd_csv_free(csv_1);

    printf("Try use other file with this conf -----------------\n\n");

    pd_csv csv_2 = pd_csv_read("res/tim_test2.csv", ',', 1);
    //t_csv csv_2 = get_test_csv_2(); 
    pd_csv_print(csv_2);
    pd_prep_prepare(&csv_2, &conf);
	pd_csv_print(csv_2);

    pd_csv_free(csv_2);

    pd_prep_free_conf(conf);
}

void    pd_csv_manual()
{
    pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
    //t_csv csv_1 = get_test_csv_1();
    pd_csv_print(csv_1);

    pd_char_a del_1[1] = {pd_strSNew("Name")};
    pd_str_a  del_str = pd_arrSNew(PD_T_STR, 1, del_1);
    pd_prep_delete(&csv_1, del_str);

    pd_char_a ohe_1[2] = {pd_strSNew("Main droite"), pd_strSNew("Zizi")};
    pd_str_a  ohe_str = pd_arrSNew(PD_T_STR, 2, ohe_1);
    pd_ohe_trees *ohe_trees = pd_prep_ohe_init(&csv_1, ohe_str);
    pd_prep_all_to_float(csv_1);
    pd_stdiz_a stdiz_data = pd_prep_strandardize_init(csv_1);
    pd_csv_print(csv_1);

    pd_csv_free(csv_1);

    printf("Try use other file with this conf -----------------\n\n");

    pd_csv csv_2 = pd_csv_read("res/tim_test2.csv", ',', 1);
    //pd_csv csv_2 = get_test_csv_2();
    pd_csv_print(csv_2);

    pd_prep_delete(&csv_2, del_str);
    pd_prep_ohe(&csv_2, ohe_trees);
    pd_prep_all_to_float(csv_2);
    pd_prep_standardize(csv_2, stdiz_data);
    pd_csv_print(csv_2);

    pd_prep_free_ohe_tree(ohe_trees);
    pd_arrRFree(del_str, -1);
    pd_arrRFree(ohe_str, -1);
    pd_arrFree(stdiz_data);
    pd_csv_free(csv_2);
}

void        tens_test(void)
{
    size_t new_shape[3] = {2, 2, 2};
    pd_tensor test = pd_tens_init(new_shape, 3);
    pd_tensor test2 = pd_tens_copy(test);
    //pd_size_t_a shape = test2.shape;
    /*for (size_t i = 0; i < shape.len; i++)
    {
        printf("%zd\n", ((size_t*)shape.val)[i]);
    }*/
    pd_tens_print(test);
    printf ("\n+\n\n");
    pd_tens_print(test2);
    printf ("\n=\n\n");
    pd_tensor test3 = pd_tens_concat(test, test2, 0);
    pd_tens_print(test3);
    test3 = pd_tens_concat(test, test2, 1);
    pd_tens_print(test3);
    test3 = pd_tens_concat(test, test2, 2);
    pd_tens_print(test3);
    pd_tens_free(test);
    pd_tens_free(test2);
    pd_tens_free(test3);
    /*shape = test3.shape;
    for (size_t i = 0; i < shape.len; i++)
    {
        printf("%zd\n", ((size_t*)shape.val)[i]);
    }*/
}

void        tens_dot_test(void)
{
    size_t shapea[5] = {5, 4, 2, 4, 5};
    size_t shapeb[5] = {5, 6, 3, 2, 1};
    size_t *new_shapea = malloc(5 * sizeof(size_t));
    new_shapea[0] = 3;
    new_shapea[1] = 4;
    new_shapea[2] = 5;
    new_shapea[3] = 6;
    new_shapea[4] = 7;
    size_t *new_shapeb = malloc(5 * sizeof(size_t));
    new_shapeb[0] = 3;
    new_shapeb[1] = 4;
    new_shapeb[2] = 5;
    new_shapeb[3] = 6;
    new_shapeb[4] = 7;
    pd_tensor a = pd_tens_init(new_shapea, 5);
    pd_tensor b = pd_tens_init(new_shapeb, 5);
    size_t **axis = malloc(2 * sizeof(float *));
    axis[0] = malloc(2 * sizeof(float));
    axis[0][0] = 0;
    axis[0][1] = 1;
    axis[1] = malloc(2 * sizeof(float));
    axis[1][0] = 3;
    axis[1][1] = 4;
    pd_tens_dot(a, b, axis);
}

int main(void)
{
    pd_time("start program");
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    printf("\n-------------- MODE CONF --------------\n");
    pd_csv_with_conf();
    printf("\n-------------- MODE MANUAL --------------\n");
    pd_csv_manual();
    tens_test();
    //t_arr test = pd_strSNew("Zizi");
    //void *test = pdmalloc(1);
    //(void)test;
    /*pd_network network;

<<<<<<< HEAD
    // tens_test();
    tens_dot_test();
    return (0);
=======
    pd_nn_init_network(&network);
    pd_nn_add(&network, pd_nn_convolution(16, 3, 2, PD_A_RELU));
    size_t pool_size[2] = {2, 2};
    pd_nn_add(&network, pd_nn_maxpool(pool_size, 2));
    pd_nn_add(&network, pd_nn_dense(16, PD_A_RELU));
    pd_nn_add(&network, pd_nn_dense(16, PD_A_RELU));
    pd_nn_validate(&network);
    pd_nn_print(network);*/
    pd_time("end program");
    pd_error("It's the end of program but I want to show the error function %s", ":)");
>>>>>>> d4088958cf1fc20314ef26d65f0685e5fbef947b
}
#include "pd_main.h"
#include <string.h>

pd_csv   get_test_csv_1(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_str_a col3[4] = {pd_str_new_s("Gros"), pd_str_new_s("Pitit"), pd_str_new_s("Moyen"), pd_str_new_s("Moyen")};
    tmp = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col3), pd_str_new_s("Zizi"));
    csv_test.begin = tmp;
    
    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_FLOAT, 4, col1), pd_str_new_s("Qi"));
    tmp = tmp->next;

    pd_str_a col2[4] = {pd_str_new_s("Timothée"), pd_str_new_s("Sylvain"), pd_str_new_s("Paco"), pd_str_new_s("Tony")};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col2), pd_str_new_s("Name"));
    tmp = tmp->next;

    pd_str_a col4[4] = {pd_str_new_s("Ca va"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée")};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col4), pd_str_new_s("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

pd_csv   get_test_csv_2(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_char_a col3[4] = {pd_str_new_s("Gros"), pd_str_new_s("Pitit"), pd_str_new_s("JSP"), pd_str_new_s("Moyen")};
    tmp = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col3), pd_str_new_s("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_FLOAT, 4, col1), pd_str_new_s("Qi"));
    tmp = tmp->next;

    pd_char_a col2[4] = {pd_str_new_s("Timothée"), pd_str_new_s("Sylvain"), pd_str_new_s("Paco"), pd_str_new_s("Tony")};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col2), pd_str_new_s("Name"));
    tmp = tmp->next;

    pd_char_a col4[4] = {pd_str_new_s("Ca va"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée"), pd_str_new_s("JSP")};
    tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col4), pd_str_new_s("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

void    pd_csv_with_conf()
{
    //pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
    pd_csv csv_1 = get_test_csv_1();
    pd_csv_print(csv_1);

    pd_char_a del_1[1] = {pd_str_new_s("Name")};
    pd_char_a ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};
    pd_csv_conf conf = pd_prep_init_conf(pd_arr_new_s(PD_T_STR, 1, del_1), pd_arr_new_s(PD_T_STR, 2, ohe_1));
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

    pd_char_a del_1[1] = {pd_str_new_s("Name")};
    pd_str_a  del_str = pd_arr_new_s(PD_T_STR, 1, del_1);
    pd_prep_delete(&csv_1, del_str);

    pd_char_a ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};
    pd_str_a  ohe_str = pd_arr_new_s(PD_T_STR, 2, ohe_1);
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
    pd_arr_free_r(del_str, -1);
    pd_arr_free_r(ohe_str, -1);
    pd_arr_free(stdiz_data);
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
    size_t *new_shapea = pd_malloc(5 * sizeof(size_t));
    new_shapea[0] = 3;
    new_shapea[1] = 4;
    new_shapea[2] = 5;
    new_shapea[3] = 6;
    new_shapea[4] = 7;
    size_t *new_shapeb = pd_malloc(5 * sizeof(size_t));
    new_shapeb[0] = 3;
    new_shapeb[1] = 4;
    new_shapeb[2] = 5;
    new_shapeb[3] = 6;
    new_shapeb[4] = 7;
    size_t *new_shapec = pd_malloc(2 * sizeof(size_t));
    new_shapec[0] = 3;
    new_shapec[1] = 4;
    size_t *new_shaped = pd_malloc(3 * sizeof(size_t));
    new_shaped[0] = 3;
    new_shaped[1] = 4;
    new_shaped[2] = 6;
    size_t *new_shapet = pd_malloc(3 * sizeof(size_t));
    new_shapet[0] = 3;
    new_shapet[1] = 2;
    new_shapet[2] = 3;
    size_t *new_shapex = pd_malloc(5 * sizeof(size_t));
    new_shapex[0] = 9;
    new_shapex[1] = 2;
    new_shapex[2] = 1;
    new_shapex[3] = 1;
    new_shapex[4] = 1;
    pd_tensor a = pd_tens_init(new_shapea, 5);
    pd_tensor b = pd_tens_init(new_shapeb, 5);
    pd_tensor c = pd_tens_init(new_shapec, 2);
    pd_tensor d = pd_tens_init(new_shaped, 3);
    pd_tensor t = pd_tens_init(new_shapet, 3);
    pd_tensor x = pd_tens_init(new_shapex, 5);
    size_t *axis1 = pd_malloc(2 * sizeof(float));
    axis1[0] = 0;
    axis1[1] = 1;
    size_t *axis2 = pd_malloc(2 * sizeof(float));
    axis2[0] = 3;
    axis2[1] = 4;
    pd_tens_reshape(t, pd_arr_new_s(PD_T_SIZE_T, 5, new_shapex));
    pd_arr axis = pd_arr_init(PD_T_ARR, 2);
    ((pd_arr *)axis.val)[0] = pd_arr_new_s(PD_T_SIZE_T, 2, axis1);
    ((pd_arr *)axis.val)[1] = pd_arr_new_s(PD_T_SIZE_T, 2, axis2);
    // pd_tens_flatten(b);
    // pd_tens_flatten(c);
    // pd_tens_flatten(d);
    pd_tens_dot(a, b, axis);
}

int main(void)
{
    // pd_time("start program");
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    // printf("\n-------------- MODE CONF --------------\n");
    // pd_csv_with_conf();
    // printf("\n-------------- MODE MANUAL --------------\n");
    // pd_csv_manual();
    // tens_test();
    tens_dot_test();
    //t_arr test = pd_str_new_s("Zizi");
    //void *test = pdmalloc(1);
    //(void)test;
    /*pd_network network;

    pd_nn_init_network(&network);
    pd_nn_add(&network, pd_nn_convolution(16, 3, 2, PD_A_RELU));
    size_t pool_size[2] = {2, 2};
    pd_nn_add(&network, pd_nn_maxpool(pool_size, 2));
    pd_nn_add(&network, pd_nn_dense(16, PD_A_RELU));
    pd_nn_add(&network, pd_nn_dense(16, PD_A_RELU));
    pd_nn_validate(&network);
    pd_nn_print(network);*/
    // pd_time("end program");
    // pd_error("It's the end of program but I want to show the error function %s", ":)");
}
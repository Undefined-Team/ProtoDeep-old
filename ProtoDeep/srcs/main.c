#include "pd_main.h"
#include <string.h>

// pd_csv   get_test_csv_1(void)
// {
//     pd_csv csv_test;
//     pd_csv_col *tmp;

//     csv_test.height = 4;
//     csv_test.width = 4;


//     pd_str_a col3[4] = {pd_str_new_s("Gros"), pd_str_new_s("Pitit"), pd_str_new_s("Moyen"), pd_str_new_s("Moyen")};
//     tmp = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col3), pd_str_new_s("Zizi"));
//     csv_test.begin = tmp;
    
//     float col1[4] = {200.77777, 1, -1, -200};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_FLOAT, 4, col1), pd_str_new_s("Qi"));
//     tmp = tmp->next;

//     pd_str_a col2[4] = {pd_str_new_s("Timothée"), pd_str_new_s("Sylvain"), pd_str_new_s("Paco"), pd_str_new_s("Tony")};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col2), pd_str_new_s("Name"));
//     tmp = tmp->next;

//     pd_str_a col4[4] = {pd_str_new_s("Ca va"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée")};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col4), pd_str_new_s("Main droite"));
//     tmp = tmp->next;

//     return csv_test;
// }

// pd_csv   get_test_csv_2(void)
// {
//     pd_csv csv_test;
//     pd_csv_col *tmp;

//     csv_test.height = 4;
//     csv_test.width = 4;


//     pd_char_a col3[4] = {pd_str_new_s("Gros"), pd_str_new_s("Pitit"), pd_str_new_s("JSP"), pd_str_new_s("Moyen")};
//     tmp = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col3), pd_str_new_s("Zizi"));
//     csv_test.begin = tmp;

//     float col1[4] = {200.77777, 1, -1, -200};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_FLOAT, 4, col1), pd_str_new_s("Qi"));
//     tmp = tmp->next;

//     pd_char_a col2[4] = {pd_str_new_s("Timothée"), pd_str_new_s("Sylvain"), pd_str_new_s("Paco"), pd_str_new_s("Tony")};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col2), pd_str_new_s("Name"));
//     tmp = tmp->next;

//     pd_char_a col4[4] = {pd_str_new_s("Ca va"), pd_str_new_s("Musclée"), pd_str_new_s("Musclée"), pd_str_new_s("JSP")};
//     tmp->next = pd_csv_new_col(pd_arr_new_s(PD_T_STR, 4, col4), pd_str_new_s("Main droite"));
//     tmp = tmp->next;

//     return csv_test;
// }

// void    pd_csv_with_conf()
// {
//     //pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
//     pd_csv csv_1 = get_test_csv_1();
//     pd_csv_print(csv_1);

//     pd_char_a del_1[1] = {pd_str_new_s("Name")};
//     pd_char_a ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};
//     pd_csv_conf conf = pd_prep_init_conf(pd_arr_new_s(PD_T_STR, 1, del_1), pd_arr_new_s(PD_T_STR, 2, ohe_1));
//     pd_prep_prepare(&csv_1, &conf);
//     pd_csv_print(csv_1);

//     pd_csv_free(csv_1);

//     printf("Try use other file with this conf -----------------\n\n");

//     pd_csv csv_2 = pd_csv_read("res/tim_test2.csv", ',', 1);
//     //t_csv csv_2 = get_test_csv_2(); 
//     pd_csv_print(csv_2);
//     pd_prep_prepare(&csv_2, &conf);
// 	pd_csv_print(csv_2);

//     pd_csv_free(csv_2);

//     pd_prep_free_conf(conf);
// }

// void    pd_csv_manual()
// {
//     pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
//     //t_csv csv_1 = get_test_csv_1();
//     pd_csv_print(csv_1);

//     pd_char_a del_1[1] = {pd_str_new_s("Name")};
//     pd_str_a  del_str = pd_arr_new_s(PD_T_STR, 1, del_1);
//     pd_prep_delete(&csv_1, del_str);

//     pd_char_a ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};
//     pd_str_a  ohe_str = pd_arr_new_s(PD_T_STR, 2, ohe_1);
//     pd_ohe_trees *ohe_trees = pd_prep_ohe_init(&csv_1, ohe_str);
//     pd_prep_all_to_float(csv_1);
//     pd_stdiz_a stdiz_data = pd_prep_strandardize_init(csv_1);
//     pd_csv_print(csv_1);

//     pd_csv_free(csv_1);

//     printf("Try use other file with this conf -----------------\n\n");

//     pd_csv csv_2 = pd_csv_read("res/tim_test2.csv", ',', 1);
//     //pd_csv csv_2 = get_test_csv_2();
//     pd_csv_print(csv_2);

//     pd_prep_delete(&csv_2, del_str);
//     pd_prep_ohe(&csv_2, ohe_trees);
//     pd_prep_all_to_float(csv_2);
//     pd_prep_standardize(csv_2, stdiz_data);
//     pd_csv_print(csv_2);

//     pd_prep_free_ohe_tree(ohe_trees);
//     pd_arr_free_r(del_str, -1);
//     pd_arr_free_r(ohe_str, -1);
//     pd_arr_free(stdiz_data);
//     pd_csv_free(csv_2);
// }

void        tens_test(void)
{
    // size_t new_shape[3] = {2, 2, 2};
    pd_tensor *test = pd_tens_init(pd_arr_shape(3, 2, 2, 2));
    pd_tensor *test2 = pd_tens_copy(test);
    pd_tens_print(test);
    printf ("\n+\n\n");
    pd_tens_print(test2);
    printf ("\n=\n\n");
    
    pd_tensor *test3 = pd_tens_concat(test, test2, 0);
    pd_tens_print(test3);
    pd_tens_free(test3);

    test3 = pd_tens_concat(test, test2, 1);
    pd_tens_print(test3);
    pd_tens_free(test3);

    test3 = pd_tens_concat(test, test2, 2);
    pd_tens_print(test3);
    pd_tens_free(test3);

    //size_t new_shape2[2] = {3, 3};
    test3 = pd_tens_init_rand(pd_arr_shape(4, 2, 3, 2, 2), 0, 10);
    pd_tens_print(test3);
    
    printf("transpose start\n");
    pd_tens_free(test2);
    test2 = pd_tens_transpose(test3, pd_arr_shape(4, 2, 1, 0, 3));
    pd_tens_print(test2);

    pd_tens_free(test3);

    pd_tens_free(test);
    pd_tens_free(test2);
}

/*void        tens_dot_test(void)
{
    // pd_tensor a = pd_tens_init(pd_arr_shape(5, 3, 4, 5, 6, 7));
    // pd_tensor b = pd_tens_init(pd_arr_shape(5, 3, 4, 5, 6, 7));
    // pd_tensor c = pd_tens_init(pd_arr_shape(2, 3, 4));
    // pd_tensor d = pd_tens_init(pd_arr_shape(3, 3, 4, 6));
    // pd_tensor t = pd_tens_init(pd_arr_shape(3, 3, 2, 3));
    // pd_tensor x = pd_tens_init(pd_arr_shape(5, 9, 2, 1, 1, 1));
    pd_tensor a = pd_tens_init_rand(pd_arr_shape(2, 3, 3), 1, 2);
    // pd_tensor a2 = pd_tens_init_rand(pd_arr_shape(5, 3, 3, 3, 3, 3), 2, 2);
    // pd_tensor a3 = pd_tens_init_rand(pd_arr_shape(5, 3, 4, 3, 4, 3), 3, 3);
    pd_tens_print(a);
    a = pd_tens_flatten(a);
    pd_tens_print(a);
    // pd_tens_print(a);
    // pd_tens_print(a2);
    // pd_tensor matrix1 = pd_tens_init(pd_arr_shape(2, 3, 6));
    // pd_tensor matrix2 = pd_tens_init(pd_arr_shape(2, 10, 3));
    // pd_arr axis = pd_arr_create(pd_arr_shape(2, 2, 2), PD_T_SIZE_T, 4, 0, 0, 4);
    // pd_arr ton_dar_le_hibou = pd_arr_create(pd_arr_shape(2, 2, 2), PD_T_STR, "ton", "dar", "le", "hibou");
    // pd_arr_print(ton_dar_le_hibou);
    // pd_tens_reshape(t, pd_arr_shape(5, 9, 2, 1, 1, 1));
    // pd_tens_flatten(b);
    // pd_tens_flatten(c);
    // pd_tens_flatten(d);
    // pd_tensor c = pd_tens_transpose(a, pd_arr_shape(5, 2, 3, 4, 1, 0));
    // pd_tensor res = pd_tens_dot(a2, a3, axis);
    // pd_tens_print(res);
    // pd_tensor add1 = pd_tens_init_rand(pd_arr_shape(4, 2, 2, 2, 2), 1, 2);
    // pd_tensor add2 = pd_tens_init_rand(pd_arr_shape(2, 4, 1), 2, 3);
    // pd_tensor addres = pd_tens_add(add1, add2);
    // pd_tens_print(add1);
    // pd_tens_print(add2);
    // pd_tens_print(addres);
    // pd_tens_print(matrix1);
    // pd_tens_print(matrix2);
    // pd_matrix_dot(matrix1, matrix2);
    // pd_tens_dot(a, b, axis);
    // pd_tens_print(matrix1);
    // pd_tens_print(matrix2);
    // pd_matrix_dot(matrix1, matrix2);
    // pd_arr test = pd_arr_create(pd_arr_shape(3, 2, 2, 2), PD_T_SIZE_T, 1, 2, 3, 4, 5, 6, 7, 8);
    // pd_arr test2 = pd_arr_create(pd_arr_shape(3, 2, 2, 2), PD_T_CHAR, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h');
    // pd_arr test3 = pd_arr_create(pd_arr_shape(3, 2, 2, 2), PD_T_FLOAT, 1, 2, 3, 4, 5, 6, 7, 8);
    // printf("%zd\n", pd_arr_size_t(test, 0, 0, 1));
    // printf("%c\n", pd_arr_char(test2, 0, 0, 1));
    // printf("%f\n", pd_arr_float(test3, 0, 0, 1));
}

void    arr_create_test()
{
    pd_arr test = pd_arr_create(pd_arr_shape(2, 2, 1), PD_T_STR, "wsh", "alors");
    pd_arr_print(test);
	pd_arr_free(test);
}*/

int main(void)
{
    // pd_time("start program");
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    // printf("\n-------------- MODE CONF --------------\n");
    // pd_csv_with_conf();
    // printf("\n-------------- MODE MANUAL --------------\n");
    // pd_csv_manual();
    tens_test();
    //tens_dot_test();
    // pd_time("normal start");
    // pd_tensor* test2 = pd_tens_init_rand(pd_arr_shape(2, 2, 2), -1, 1);
    // pd_tens_print(test2);
    // pd_tensor* test3 = pd_tens_copy(test2);
    // pd_tens_print(test3);
    // pd_tensor* test4 = pd_tens_concat(test2, test3, -1);
    // pd_tens_print(test4);
    // pd_tens_free(test2);
    // pd_tens_free(test3);
    // pd_tens_free(test4);
    // pd_time("normal end");
    //printf("salut fdp\n");
    //pd_tens_print(test);
    // arr_create_test();
    // printf("\n-------------- MODE CONF --------------\n");
    // pd_csv_with_conf();
    // printf("\n-------------- MODE MANUAL --------------\n");
    // pd_csv_manual();
    // tens_test();
    //tens_dot_test();
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

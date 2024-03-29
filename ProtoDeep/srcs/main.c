#include "pd_main.h"
#include <string.h>

pd_csv   get_test_csv_1(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_str_a *col3 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Gros", "Pitit", "Moyen", "Moyen");
    tmp = pd_csv_new_col(col3, pd_str_new_s("Zizi"));
    csv_test.begin = tmp;
    
    pd_float_a *col1 = pd_arr_create(pd_arr_shape(1, 4), PD_T_FLOAT, 200.77777, 1, -1, -200);
    tmp->next = pd_csv_new_col(col1, pd_str_new_s("Qi"));
    tmp = tmp->next;

    pd_str_a *col2 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Timothee", "Sylvain", "Paco", "Tony");
    tmp->next = pd_csv_new_col(col2, pd_str_new_s("Name"));
    tmp = tmp->next;

    pd_str_a *col4 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Ca va", "Musclee", "Musclee", "Pas trop");
    tmp->next = pd_csv_new_col(col4, pd_str_new_s("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

pd_csv   get_test_csv_2(void)
{
    pd_csv csv_test;
    pd_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    pd_char_a *col3 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Gros", "Pitit", "JSP", "Moyen");
    tmp = pd_csv_new_col(col3, pd_str_new_s("Zizi"));
    csv_test.begin = tmp;

    pd_float_a *col1 = pd_arr_create(pd_arr_shape(1, 4), PD_T_FLOAT, 200.77777, 1, -1, -200);
    tmp->next = pd_csv_new_col(col1, pd_str_new_s("Qi"));
    tmp = tmp->next;

    pd_char_a *col2 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Timothee", "Sylvain", "Paco", "Tony");
    tmp->next = pd_csv_new_col(col2, pd_str_new_s("Name"));
    tmp = tmp->next;

    pd_char_a *col4 = pd_arr_create(pd_arr_shape(1, 4), PD_T_STR, "Ca va", "Musclee", "Musclee", "Pas trop");
    tmp->next = pd_csv_new_col(col4, pd_str_new_s("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

void    pd_csv_with_conf()
{
    pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
    //pd_csv csv_1 = get_test_csv_1();
    pd_csv_print(csv_1);

    pd_char_a *del_1[1] = {pd_str_new_s("Name")};
    pd_char_a *ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};

    pd_csv_conf conf = pd_prep_init_conf(pd_arr_new_s(PD_T_STR, 1, del_1), pd_arr_new_s(PD_T_STR, 2, ohe_1));
    pd_prep_prepare(&csv_1, &conf);
    pd_csv_print(csv_1);

    pd_csv_free(csv_1);

    printf("Try use other file with this conf -----------------\n\n");

    pd_csv csv_2 = pd_csv_read("res/tim_test2.csv", ',', 1);
    //pd_csv csv_2 = get_test_csv_2();
    pd_csv_print(csv_2);
    pd_prep_prepare(&csv_2, &conf);
	pd_csv_print(csv_2);

    pd_csv_free(csv_2);

    pd_prep_free_conf(conf);
}

void    pd_csv_manual()
{
    pd_csv csv_1 = pd_csv_read("res/tim_test1.csv", ',', 1);
    //pd_csv csv_1 = get_test_csv_1();
    pd_csv_print(csv_1);

    pd_char_a *del_1[1] = {pd_str_new_s("Name")};
    pd_str_a  *del_str = pd_arr_new_s(PD_T_STR, 1, del_1);
    pd_prep_delete(&csv_1, del_str);

    pd_char_a *ohe_1[2] = {pd_str_new_s("Main droite"), pd_str_new_s("Zizi")};
    pd_str_a  *ohe_str = pd_arr_new_s(PD_T_STR, 2, ohe_1);
    pd_ohe_trees *ohe_trees = pd_prep_ohe_init(&csv_1, ohe_str);
    pd_prep_all_to_float(csv_1);
    pd_stdiz_a *stdiz_data = pd_prep_strandardize_init(csv_1);
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
    // size_t new_shape[3] = {2, 2, 2};
   /* pd_tensor *test = pd_tens_init_rand(pd_arr_shape(3, 2, 2, 2), -1, 1);
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
    pd_tens_free(test2);*/
}

void        tens_dot_test(void)
{
    // pd_tensor *test = pd_tens_init_rand(pd_arr_shape(3, 1, 2, 3), -1, 1);
    // pd_tens_print(test);
    // pd_tens_print(test);
    // pd_tensor *flat = pd_tens_flatten(test);
    // pd_tens_print(flat);
    // pd_tensor *reshape = pd_tens_reshape(flat, pd_arr_shape(3, 3, 2, 1));
    // pd_tens_print(reshape);
    // pd_tensor *a = pd_tens_init_rand(pd_arr_shape(5, 3, 4, 5, 6, 7), 2, 2);
    // pd_tensor *b = pd_tens_init_rand(pd_arr_shape(5, 3, 4, 5, 6, 7), 3, 3);
    // pd_tensor c = pd_tens_init(pd_arr_shape(2, 3, 4));
    // pd_tensor d = pd_tens_init(pd_arr_shape(3, 3, 4, 6));
    // pd_tensor t = pd_tens_init(pd_arr_shape(3, 3, 2, 3));
    // pd_tensor x = pd_tens_init(pd_arr_shape(5, 9, 2, 1, 1, 1));
    // pd_tensor a = pd_tens_init_rand(pd_arr_shape(2, 3, 3), 1, 2);
    //pd_tensor *a2 = pd_tens_init_rand(pd_arr_shape(4, 1, 2, 3, 4), 1, 2);
    // pd_tens_print(a2);
    // pd_tens_print(a2);
    //pd_tens_print(a2);
    // pd_tensor *a3 = pd_tens_init_rand(pd_arr_shape(5, 3, 4, 3, 4, 3), 3, 3);
    // pd_tens_print(a);
    // a = pd_tens_flatten(a);
    // pd_tens_print(a);
    // pd_tens_print(a);
    // pd_tens_print(a2);
    // pd_tensor matrix1 = pd_tens_init(pd_arr_shape(2, 3, 6));
    // pd_tensor matrix2 = pd_tens_init(pd_arr_shape(2, 10, 3));
    // pd_arr *axis = pd_arr_create(pd_arr_shape(2, 2, 2), PD_T_SIZE_T, 4, 0, 0, 4);
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
    //for (size_t i = 0; i < 500; i++) {
    //     pd_tensor *reshape = pd_tens_flatten(a2);
    //    pd_tens_free(reshape);
    //}
    // pd_tens_print(reshape);
    // pd_tens_print(flat);
    // for (size_t i = 0; i < 1000; i++)
    // {
    //     pd_tensor *dot = pd_tens_dot(a2, a3, pd_arr_copy(axis));
    //     pd_tens_free(dot);
    // }
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

/*void    arr_create_test()
{
    pd_arr test = pd_arr_create(pd_arr_shape(2, 2, 1), PD_T_STR, "wsh", "alors");
    pd_arr_print(test);
	pd_arr_free(test);
}*/

// void    transpose_init_main(void)
// {
//     pd_tensor *test;
//     for(size_t i = 0; i < 10; i++)
//     {
//         test = pd_tens_init_val(pd_arr_shape(10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1), 2);
//         pd_tens_free(test);
//     }
// }

// void    paco_main(void)
// {
//     pd_tensor *test = pd_tens_init_val(pd_arr_shape(10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1), 2);
//     //pd_tens_print(test) --> pour print un tensor 
//     pd_tensor *transposed;
//     for(size_t i = 0; i < 10; i++)
//     {
//         transposed = pd_tens_transpose(test, pd_arr_shape(10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
//         pd_tens_free(transposed);
//     }
// }

void    new_tens_main(void)
{
    // pd_tensor *tensor = pd_tens_init_val(pd_arr_shape(3, 2, 2, 2), 2);
    // printf("eeee\n");
    // for (size_t i = 0; i < tensor->shape_len; ++i)
    //     printf("%zd\n", tensor->shape_m[i]);
    // printf("%zd\n", tensor->len);
    // for (size_t z = 0; z < 2; z++)
    // {
    //     for (size_t y = 0; y < 2; y++)
    //     {
    //         for (size_t x = 0; x < 2; x++)
    //         {
    //             printf("%f ", pd_tens_get_val(tensor, z, y, x));
    //         }
    //     }   
    // }
    // printf("\n");
    // pd_tensor *test;
    // for (size_t i = 1; i < 10; i++)
    // {
    //     test = pd_tens_init_val(pd_arr_shape(10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1), 2);
    //     pd_free(test->val);
    //     pd_free(test->shape);
    //     pd_free(test->shape_m);
    //     pd_free(test);
    //     // pd_tens_free(test);
    // }

    
    // pd_tensor *test = pd_tens_init_val(pd_arr_shape(1, 1000000000), 2);
    // float val;
    // for (size_t i = 0; i < 10; i++)
    //     val = pd_tens_get_mval(test, 999999999);
    
    pd_tensor *test = pd_tens_init_rand(pd_arr_shape(2, 1, 1), -10 , 10);
    pd_tens_print(test);
    pd_tensor *test2 = pd_tens_cpy(test);
    pd_tens_free(test);
    pd_tens_print(test2);
    pd_tensor *test3 = pd_tens_get(test2, pd_arr_shape(1, 0));
    pd_tensor *test4 = pd_tens_get_cpy(test2, pd_arr_shape(1, 0));
    pd_tens_print(test3);
    pd_free(test3);
    pd_tens_free(test2);
    pd_tens_print(test4);
    pd_tens_free(test4);

    test = pd_tens_init_id(pd_arr_shape(4, 2, 3, 4, 5));
    // test = pd_tens_init_id(pd_arr_shape(5, 5, 4, 3, 2, 1));
    pd_tens_print(test);

    test2 = pd_tens_transpose_cpy(test, pd_arr_shape(4, 1, 0, 3, 2));
    // test2 = pd_tens_transpose_cpy(test, pd_arr_shape(4, 3, 0, 1, 2));

    // test2 = pd_tens_transpose_cpy(test, pd_arr_shape(5, 4, 3, 1, 0, 2));
    pd_tens_print(test2);
    pd_tens_free(test2);

    // pd_tens_transpose(test, pd_arr_shape(4, 3, 1, 0, 2));
    // pd_tens_transpose(test, pd_arr_shape(5, 4, 3, 1, 0, 2));
    // pd_tens_print(test);
    // pd_tens_transpose_2(test, pd_arr_shape(3, 0, 2, 1));
    // printf("%f\n", pd_tens_get_mval(test, 1, 1, 1, 0));
    // pd_tens_print(test);
    pd_tens_free(test);
}

void flatten_main()
{
    for (size_t i = 0; i < 1; i++)
    {
        pd_tensor *tens = pd_tens_init_val(pd_arr_shape(3, 5, 5, 5), 2);
        pd_tens_print(tens);
        pd_tensor *flat = pd_tens_flatten(tens);
        pd_tens_print(flat);
        pd_tensor *reshape = pd_tens_reshape(flat, pd_arr_shape(3, 25, 0, 5));
        pd_tens_print(reshape);
        free(tens->val);
        free(tens->shape);
        free(tens->shape_m);
    }
}

void    pd_transpose_test(void)
{
    // pd_tensor *test = pd_tens_init_id(pd_arr_shape(10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1));
    // pd_tens_transpose_2(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
    // pd_tens_transpose(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
    // pd_tensor *test2;
    // for (size_t i = 0; i < 100; ++i)
    // {
    //     // test2 = pd_tens_transpose_cpy(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
    //     test2 = pd_tens_transpose_2(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
    //     pd_tens_free(test2);
    // }
    // pd_tensor *test = pd_tens_init_id(pd_arr_shape(3, 3, 2, 2));
    // pd_tens_print(test);
    // pd_tensor *test2 = pd_tens_transpose_cpy(test, pd_arr_shape(3, 1, 2, 0));
    // pd_tens_print(test2);
    //     pd_tens_print(test);

    // pd_tensor *test3 = pd_tens_transpose_cpy_2(test, pd_arr_shape(3, 1, 2, 0));
    // pd_tens_print(test3);
    // pd_tens_free(test3);
    // pd_tens_free(test2);
    // pd_tens_free(test);
    // pd_tensor *test4 = pd_tens_init_id();
    // pd_tensor *test3 = pd_tens_transpose_cpy_2(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));

    pd_tensor *test = pd_tens_init_id(pd_arr_shape(10, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1));
    pd_tensor *test2;
    for (size_t i = 0; i < 100; i++)
    {
        // test2 = pd_tens_transpose_cpy_2(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
        test2 = pd_tens_transpose_cpy(test, pd_arr_shape(10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
        pd_tens_free(test2);
    }
    
}

int main(void)
{
    // pd_time("start program");
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    //printf("\n-------------- MODE CONF --------------\n");
    //pd_csv_with_conf();
    //printf("\n-------------- MODE MANUAL --------------\n");
    //pd_csv_manual();
    //tens_test();
    //tens_dot_test();
    //paco_main();
    // pd_tensor *test = pd_tens_init_val(pd_arr_shape(2, 2, 2), 2);
    // pd_tens_print(test);
    // exit(0);
    // transpose_init_main();
    // new_tens_main();
    // flatten_main();
    // new_old_init_main();
    pd_transpose_test();
}

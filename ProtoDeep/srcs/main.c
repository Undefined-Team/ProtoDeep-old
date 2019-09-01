#include "pd_main.h"
#include <string.h>
t_csv   get_test_csv_1(void)
{
    t_csv csv_test;
    t_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    t_char_a col3[4] = {strSNew("Gros"), strSNew("Pitit"), strSNew("Moyen"), strSNew("Moyen")};
    tmp = dast_csv_new_col(arrSNew(T_STR, 4, col3), strSNew("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = dast_csv_new_col(arrSNew(T_FLOAT, 4, col1), strSNew("Qi"));
    tmp = tmp->next;

    t_char_a col2[4] = {strSNew("Timothée"), strSNew("Sylvain"), strSNew("Paco"), strSNew("Tony")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col2), strSNew("Name"));
    tmp = tmp->next;

    t_char_a col4[4] = {strSNew("Ca va"), strSNew("Musclée"), strSNew("Musclée"), strSNew("Musclée")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col4), strSNew("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

t_csv   get_test_csv_2(void)
{
    t_csv csv_test;
    t_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 4;


    t_char_a col3[4] = {strSNew("Gros"), strSNew("Pitit"), strSNew("JSP"), strSNew("Moyen")};
    tmp = dast_csv_new_col(arrSNew(T_STR, 4, col3), strSNew("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200.77777, 1, -1, -200};
    tmp->next = dast_csv_new_col(arrSNew(T_FLOAT, 4, col1), strSNew("Qi"));
    tmp = tmp->next;

    t_char_a col2[4] = {strSNew("Timothée"), strSNew("Sylvain"), strSNew("Paco"), strSNew("Tony")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col2), strSNew("Name"));
    tmp = tmp->next;

    t_char_a col4[4] = {strSNew("Ca va"), strSNew("Musclée"), strSNew("Musclée"), strSNew("JSP")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col4), strSNew("Main droite"));
    tmp = tmp->next;

    return csv_test;
}

void    csv_with_conf()
{
    t_csv csv_1 = csv_read("res/tim_test1.csv", ',', 1);
    //t_csv csv_1 = get_test_csv_1();
    csv_print(csv_1);

    t_char_a del_1[1] = {strSNew("Name")};
    t_char_a ohe_1[2] = {strSNew("Main droite"), strSNew("Zizi")};
    t_csv_conf conf = prep_init_conf(arrSNew(T_STR, 1, del_1), arrSNew(T_STR, 2, ohe_1));
    prep_prepare(&csv_1, &conf);
    csv_print(csv_1);

    csv_free(csv_1);

    printf("Try use other file with this conf -----------------\n\n");

    t_csv csv_2 = csv_read("res/tim_test2.csv", ',', 1);
    //t_csv csv_2 = get_test_csv_2(); 
    csv_print(csv_2);
    prep_prepare(&csv_2, &conf);
	csv_print(csv_2);

    csv_free(csv_2);

    prep_free_conf(conf);
}

void    csv_manual()
{
    t_csv csv_1 = csv_read("res/tim_test1.csv", ',', 1);
    //t_csv csv_1 = get_test_csv_1();
    csv_print(csv_1);

    t_char_a del_1[1] = {strSNew("Name")};
    t_str_a  del_str = arrSNew(T_STR, 1, del_1);
    prep_delete(&csv_1, del_str);

    t_char_a ohe_1[2] = {strSNew("Main droite"), strSNew("Zizi")};
    t_str_a  ohe_str = arrSNew(T_STR, 2, ohe_1);
    t_ohe_trees *ohe_trees = prep_ohe_init(&csv_1, ohe_str);

    prep_all_to_float(csv_1);
    t_stdiz_a stdiz_data = prep_strandardize_init(csv_1);
    csv_print(csv_1);

    csv_free(csv_1);

    printf("Try use other file with this conf -----------------\n\n");

    t_csv csv_2 = csv_read("res/tim_test2.csv", ',', 1);
    //t_csv csv_2 = get_test_csv_2();
    csv_print(csv_2);

    prep_delete(&csv_2, del_str);
    prep_ohe(&csv_2, ohe_trees);
    prep_all_to_float(csv_2);
    prep_standardize(csv_2, stdiz_data);
    csv_print(csv_2);

    prep_free_ohe_tree(ohe_trees);
    arrRFree(del_str, -1);
    arrRFree(ohe_str, -1);
    arrFree(stdiz_data);
    csv_free(csv_2);
}

int main(void)
{
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    printf("\n-------------- MODE CONF --------------\n");
    csv_with_conf();
    printf("\n-------------- MODE MANUAL --------------\n");
    csv_manual();
    //t_arr test = strSNew("Zizi");
    //void *test = pdmalloc(1);
    //(void)test;
    return (0);
}

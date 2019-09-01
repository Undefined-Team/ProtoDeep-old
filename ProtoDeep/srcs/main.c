#include "pd_main.h"
#include <string.h>
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

int main(void)
{
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_csv_print(csv);
    printf("\n-------------- MODE CONF --------------\n");
    pd_csv_with_conf();
    printf("\n-------------- MODE MANUAL --------------\n");
    pd_csv_manual();
    //t_arr test = pd_strSNew("Zizi");
    //void *test = pdmalloc(1);
    //(void)test;
    return (0);
}

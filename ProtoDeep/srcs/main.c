#include "pd_main.h"
#include <string.h>

t_csv   get_test_csv(void)
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

void    tim_main()
{
    t_csv csv_1 = get_test_csv();
    dbug_print_csv(csv_1);

    t_char_a del_1[1] = {strSNew("Name")};
    t_char_a ohe_1[2] = {strSNew("Main droite"), strSNew("Zizi")};
    t_csv_conf conf = prep_init_conf(arrSNew(T_STR, 1, del_1), arrSNew(T_STR, 2, ohe_1));
    prep_prepare(&csv_1, &conf);
    dbug_print_csv(csv_1);

    for (t_ohe_trees *test = conf.saved_trees; test; test = test->next)
        printf("%s\n", (char*)test->base_name.val);

    prep_free_conf(conf);
    csv_free(csv_1);

    printf("-----------------\n\n");

   /* t_csv csv_2 = get_test_csv();
    dbug_print_csv(csv_2);

    t_char_a del_2[1] = {strSNew("Name")};
    t_str_a  del_str = arrSNew(T_STR, 1, del_2);
    prep_delete(&csv_2, del_str);
    dbug_print_csv(csv_2);

    t_char_a ohe_2[2] = {strSNew("Main droite"), strSNew("Zizi")};
    t_str_a  ohe_str = arrSNew(T_STR, 2, ohe_2);
    prep_ohe(&csv_2, ohe_str);
    dbug_print_csv(csv_2);

    prep_all_to_float(csv_2);
    t_stdiz_a stdiz_data = prep_strandardize_init(csv_2);
    (void)stdiz_data;
    dbug_print_csv(csv_2);

    arrRFree(del_str, -1);
    arrRFree(ohe_str, -1);
    arrFree(stdiz_data);
    csv_free(csv_2);*/

}

int main(void)
{
    //t_csv   csv = csv_read("./test.csv", 1);
    //dbug_print_csv(csv);
    tim_main();
    
    //t_arr test = strSNew("Zizi");
    //void *test = pdmalloc(1);
    //(void)test;
    return (0);
}
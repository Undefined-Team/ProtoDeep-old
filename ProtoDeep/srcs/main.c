#include "pd_main.h"
#include <string.h>

t_csv   get_test_csv(void)
{
    t_csv csv_test;
    t_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 3;


    t_char_a col3[4] = {strSNew("Gros"), strSNew("Pitit"), strSNew("Moyen"), strSNew("Moyen")};
    //t_str col3[4] = {strSNew("Moyen"), strSNew("Moyen"), strSNew("Moyen"), strSNew("Moyen")};
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

void    tim_main(void)
{
    t_csv test_csv = get_test_csv();
    dbug_print_csv(test_csv);
    /*size_t ci[2] = {0, 3};
    prep_ohe(&test_csv, arrSNew(T_SIZE_T, 2, ci));
    dbug_print_csv(test_csv);*/
    size_t del_i[1] = {2};
    size_t ohe_i[2] = {0, 3};
    t_csv_conf conf = prep_init_conf(arrSNew(T_SIZE_T, 1, del_i), arrSNew(T_SIZE_T, 2, ohe_i));
    (void)conf;
    prep_prepare(&test_csv, &conf);
    //prep_ohe(&test_csv, arrSNew(T_SIZE_T, 2, ohe_i));
    dbug_print_csv(test_csv);
}

int main(void)
{
    tim_main();
    return (0);
}
#include "pd_main.h"
#include <string.h>

t_csv   get_test_csv(void)
{
    t_csv csv_test;
    t_csv_col *tmp;

    csv_test.height = 4;
    csv_test.width = 3;


    t_str col3[4] = {strSNew("Gros"), strSNew("Pitit"), strSNew("Moyen"), strSNew("Moyen")};
    //t_str col3[4] = {strSNew("Moyen"), strSNew("Moyen"), strSNew("Moyen"), strSNew("Moyen")};
    tmp = dast_csv_new_col(arrSNew(T_STR, 4, col3), strSNew("Zizi"));
    csv_test.begin = tmp;

    float col1[4] = {200, 1, -1, -200};
    tmp->next = dast_csv_new_col(arrSNew(T_FLOAT, 4, col1), strSNew("Qi"));
    tmp = tmp->next;

    t_str col2[4] = {strSNew("Timothée"), strSNew("Sylvain"), strSNew("Paco"), strSNew("Tony")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col2), strSNew("Name"));
    tmp = tmp->next;

    t_str col4[4] = {strSNew("Ca va"), strSNew("Musclée"), strSNew("Musclée"), strSNew("Musclée")};
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 4, col4), strSNew("Main droite"));
    tmp = tmp->next;
    
    /*t_str col4[2] = {
                        strSNew("Pas bridé"),
                        strSNew("bridé")
                    };
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 2, col4), strSNew("Yeux"));
    tmp = tmp->next;

    t_str col5[2] = {
                        strSNew("Adidas blanche"),
                        strSNew("Adidas noir")
                    };
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 2, col5), strSNew("Casquette"));
    tmp = tmp->next;

    t_str col6[2] = {
                        strSNew("Pas cassé"),
                        strSNew("Cassé")
                    };
    tmp->next = dast_csv_new_col(arrSNew(T_STR, 2, col6), strSNew("Ordinateur"));
    tmp = tmp->next;*/

    return csv_test;
}

int main(void)
{
    csv_read("./test.csv", 0);
    return (0);
}
#include "pd_main.h"
#include <string.h>

t_csv   get_test_csv(void)
{
    t_csv csv_test;

    csv_test.height = 2;
    csv_test.width = 2;
    
    csv_test.begin = dast_csv_new_col(1, 2, dast_new_static_carr("Poids", 5));
    t_csv_col *test = csv_test.begin;
    printf("OK2\n");
    t_farr converted = *( (t_farr*) (test->columns) );
    printf("test = %zd\n", converted.len);
    //(*converted)->arr = (float*)((*converted)->arr);
    converted.arr[0] = 58.777;


    
    printf("OK3\n");
    /*((t_farr*)test->columns)->arr[1] = 1;

    test->next = dast_csv_new_col(0, 2, dast_new_static_carr("Name", 4));

    test = test->next;

    ((t_starr*)test->columns)->arr[0].arr = "Timothée";
    ((t_starr*)test->columns)->arr[0].len = 8;
    ((t_starr*)test->columns)->arr[1].arr = "Sylvain";
    ((t_starr*)test->columns)->arr[1].len = 7;
*/
    return csv_test;
}

int main(void)
{
    //if (!ac && av)
    //    return (0);
    //csv_read("test.csv", 0);
    t_siarr truck;

    truck.arr = malloc(sizeof(size_t) * 5);
    truck.len = 5;
    truck.arr[0] = 100;
    truck.arr[1] = 2;
    truck.arr[2] = 4;
    truck.arr[3] = 1;
    truck.arr[4] = 3;
    math_si_sort(truck);
    for (size_t i = 0; i < truck.len; i++)
    {
        printf("-> %zd \n", truck.arr[i]);
    }

    float test[7] = {100.1, 2.4544544545454, 5, 7.97352, -100.55555, 0, 100};
    for (size_t i = 0; i < 7; i++)
    {
        printf ("% *g|\n", 8, test[i]);
    }

    char *test3[3] = {"slt", "ca va", "   cc"};
    for (size_t i = 0; i < 3; i++)
    {
        printf ("%*s>\n", 5, test3[i]);
    }

    t_csv test_csv = get_test_csv();
    printf("GET CSV DONE\n");
    dbug_print_csv(test_csv);
    return (0);
}
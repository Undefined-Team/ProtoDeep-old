#include "pd_main.h"
#include <string.h>

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
    return (0);
}
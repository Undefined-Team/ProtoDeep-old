
#include <stdlib.h>
#include <stdio.h>

typedef struct      s_carr { // Char array (String)
    char           *arr;
    size_t          len;
}                   t_carr;

typedef struct      s_iarr {
    int             *arr;
    size_t          len;
}                   t_iarr;

typedef struct      s_farr {
    float           *arr;
    size_t          len;
}                   t_farr;

typedef struct      s_varr {
    void            *arr;
    size_t          len;
}                   t_varr;

typedef struct      s_csv_col {
    size_t              len;
    t_carr              name;
    struct s_csv_col    *next;
    int                 type;
    void                *columns;
}                   t_csv_col;

t_varr  dast_init_varr(size_t len, size_t so)
{
    t_varr new_array;

    new_array.len = len;
    new_array.arr = malloc(sizeof(so) * len);
    return new_array;
}

t_csv_col   *dast_csv_new_col(int type, size_t len)
{
    t_csv_col   *elem = NULL;
    t_varr      tmp;

    elem = malloc(sizeof(t_csv_col));
    if (type == 0)
    {
        tmp = dast_init_varr(len, sizeof(int)); // <-- And here the same for int
        elem->columns = &tmp;
    }
    else
    {
        tmp = dast_init_varr(len, sizeof(float)); // <-- I use size of float
        elem->columns = &tmp;
    }
    return (elem);
}

int main(void)
{
    t_csv_col *test = dast_csv_new_col(2, 5); // Type 2 == float
    t_farr converted = *( (t_farr*) (test->columns) );
    converted.arr[0] = 0.5; // --> Segfault
    printf("%zd %f\n", converted.len, converted.arr[0]);
    return 0;
}
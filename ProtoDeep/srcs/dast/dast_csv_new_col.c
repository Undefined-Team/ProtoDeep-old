#include "pd_main.h"

t_csv_col   *dast_csv_new_col(int type, size_t len, t_carr name)
{
    t_csv_col   *elem = NULL;
    t_varr      tmp;

        printf("OK6\n");

    PROT_MALLOC(elem = malloc(sizeof(t_csv_col)));
    elem->name = name;
    elem->len = len;
    elem->next = NULL;
    elem->type = type;
    if (type == 0)
    {
        //tmp = dast_init_varr(len, sizeof(char*));
        //elem->columns = &tmp;
        
        tmp = dast_init_varr(len, sizeof(t_carr));
        elem->columns = &tmp;

        //t_varr *tmp2 = &tmp;
        //elem->columns = dast_init_varr(len, sizeof(char*));
        //elem->columns = (t_starr*)(&tmp);
    }
    else if (type == 1)
    {
        //tmp = dast_init_varr(len, sizeof(float));
        //elem->columns = &tmp;
        
        tmp = dast_init_varr(len, sizeof(float));
        elem->columns = &tmp;

        //t_varr *tmp2 = &tmp;
        //elem->columns = dast_init_varr(len, sizeof(float));
        //elem->columns = (t_farr*)(&tmp);
    }
    return (elem);
}
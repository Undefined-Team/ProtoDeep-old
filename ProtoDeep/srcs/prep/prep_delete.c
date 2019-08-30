#include "pd_main.h"

void    prep_delete(t_csv *csv, t_str_a col_names)
{
    // Error if col is not of type t_carr
    // Error if indexs in ohe_indexs is out of range
    t_csv_col   *col = csv->begin;
    size_t      i = 0;
    t_csv_col   *before = NULL;
    t_csv_col   *tmp = NULL;

    col_names = dast_name_sort(*csv, col_names);
    while (col && i < col_names.len)
    {
        if (str_cmp((char*)col->name.val, (char*)(((t_str_a*)col_names.val)[i].val) ) == 0)
        {
            tmp = col;
            col = col->next;
            if (before)
                before->next = col;
            else
                csv->begin = col;
            dast_csv_free_col(tmp);
            i++;
        }
        if (!col)
            break;
        before = col;
        col = col->next;
    }
    i = 0;
    for (col = csv->begin; col; col = col->next)
        i++;
    csv->width = i;
    arrFree(col_names);
}

/*

- Faire que *col = last_col pour mieux utiliser les i et economiser des lignes
- Sauvegarder l arbre binaire dans conf
- Faire une fonction d utilisation de l arbre binaire (Si un mot n est pas trouve alors 0 dans chaque ligne)

*/
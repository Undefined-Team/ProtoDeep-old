#include "pd_main.h"

t_size_t_a  dast_name_sort(t_csv csv, t_str_a col_ni)
{
    for (t_csv_col *col = csv.begin; col; col = col->next)
    {
        for (size_t i = 0; i < col_ni.len; i++)
        {
            if (str_cmp( (char*)(((t_char_a*)col_ni.val)[i].val), (char*)col->name ) == 0)
            {
                
            }
        }
    }
}
#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro
# define CSV_STR 0
# define CSV_FLOAT 1

// Structures
typedef struct              s_tokens_list
{
    struct s_tokens_list    *next;
    t_arr                   tokens;
}                           t_tokens_list;

// Prototypes
t_csv_col   *csv_read(char *file_name, int header);

#endif
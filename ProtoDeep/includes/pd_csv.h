#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro

// Structures
typedef struct          s_csv_char_col
{
    t_carr              *values;
    int                 type;
}                       t_csv_char_col;

typedef struct          s_csv_col
{
    size_t              len;
    t_carr              name;
    struct s_csv_col    *next;
    void                *columns;
}                       t_csv_col;

// Prototypes
t_csv_col   csv_read(char *file_name, int header);
t_csv_col   *dast_csv_new_col(int type, size_t len, char *name);

#endif
#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro
# define CSV_STR 0
# define CSV_FLOAT 1

// Structures


// Prototypes
t_csv_col   csv_read(char *file_name, int header);
t_csv_col   *dast_csv_new_col(int type, size_t len, char *name);

#endif
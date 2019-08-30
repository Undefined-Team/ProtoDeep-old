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
t_csv           csv_read(char *file_name, int header);
t_csv_col       *create_cols(t_tokens_list *tokens, int header, size_t width, size_t height);
t_tokens_list   *csv_create_tokens_list(int fd, size_t *height, size_t *width);
void            csv_free_tokens_list(t_tokens_list *tokens);
void            csv_free(t_csv csv);

#endif
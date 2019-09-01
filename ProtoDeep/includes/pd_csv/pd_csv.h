#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro
# define CSV_STR 0
# define CSV_FLOAT 1

# define DBUG_PREC 3

# define COLOR_N    "\x1b[0m"
# define COLOR_U    "\x1b[4m"
# define COLOR_1    "\x1b[38;2;68;175;105m"
# define COLOR_2    "\x1b[38;2;248;51;60m"
# define COLOR_3    "\x1b[38;2;43;158;179m"
# define COLOR_4    "\x1b[38;2;255;127;17m"
# define COLOR_5    "\x1b[38;2;255;1;251m"
# define COLOR_T     {COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5}

// Structures
typedef struct              s_tokens_list
{
    struct s_tokens_list    *next;
    t_arr                   tokens;
}                           t_tokens_list;

// Prototypes
t_csv           csv_read(char *file_name, char separator, int header);
t_csv_col       *create_cols(t_tokens_list *tokens, int header, size_t width, size_t height);
t_tokens_list   *csv_create_tokens_list(int fd, char separator, size_t *height, size_t *width);
void            csv_free_tokens_list(t_tokens_list *tokens);
void            csv_free(t_csv csv);
void            csv_print(t_csv csv);

#endif
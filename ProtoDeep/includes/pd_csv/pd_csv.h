#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro
# define PD_CSV_STR            0
# define PD_CSV_FLOAT          1

# define PD_DBUG_PREC          3

# define PD_COLOR_N            "\x1b[0m"
# define PD_COLOR_U            "\x1b[4m"
# define PD_COLOR_1            "\x1b[38;2;68;175;105m"
# define PD_COLOR_2            "\x1b[38;2;248;51;60m"
# define PD_COLOR_3            "\x1b[38;2;43;158;179m"
# define PD_COLOR_4            "\x1b[38;2;255;127;17m"
# define PD_COLOR_5            "\x1b[38;2;255;1;251m"
# define PD_COLOR_T            {COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5}

// Structures
typedef struct              pds_tokens_list {
    struct pds_tokens_list  *next;
    pd_arr                  tokens;
}                           pd_tokens_list;

typedef struct              pds_csv_col {
    pd_arr                  name;
    struct pds_csv_col      *next;
    pd_arr                  columns;
}                           pd_csv_col;

typedef struct              pds_csv {
    pd_csv_col              *begin;
    size_t                  width;
    size_t                  height;
}                           pd_csv;

// Prototypes
pd_csv                      pd_csv_read(char *file_name, char separator, int header);
pd_csv_col                  *pd_csv_create_cols(pd_tokens_list *tokens, int header, size_t width, size_t height);
pd_tokens_list              *pd_csv_create_tokens_list(int fd, char separator, size_t *height, size_t *width);
void                        pd_csv_free_tokens_list(pd_tokens_list *tokens);
void                        pd_csv_free(pd_csv csv);
void                        pd_csv_print(pd_csv csv);
pd_csv_col                  *pd_csv_new_col(pd_arr columns, pd_char_a name);
void                        pd_csv_free_col(pd_csv_col *elem);

#endif
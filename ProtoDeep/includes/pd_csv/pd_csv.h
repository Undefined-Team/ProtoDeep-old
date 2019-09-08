#ifndef PD_CSV_H
# define PD_CSV_H

// Lib

// Macro
# define PD_DBUG_PREC        3

// Structures
typedef struct              pds_tokens_list {
    struct pds_tokens_list  *next;
    pd_arr                  *tokens;
}                           pd_tokens_list;

typedef struct              pds_csv_col {
    pd_arr                  *name;
    struct pds_csv_col      *next;
    pd_arr                  *columns;
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
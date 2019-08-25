#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
# define PROT_MALLOC(x)         if (!(x)) {return NULL;}

// Structures
typedef enum {false,true} bool;

typedef struct      s_farr {
    float           *arr;
    size_t          len;
}                   t_farr;

typedef struct      s_carr { // Char array (String)
    char           *arr;
    size_t          len;
}                   t_carr;

typedef struct      s_siarr {
    size_t          *arr;
    size_t          len;
}                   t_siarr;

typedef struct      s_starr { // String array
    t_carr          *arr;
    size_t          len;
}                   t_starr;

// -----------------

typedef struct          s_csv_str_col
{
    t_starr             arr;
    int                 type;
}                       t_csv_str_col;

typedef struct          s_csv_float_col
{
    t_farr              arr;
    int                 type;
}                       t_csv_float_col;

typedef struct          s_csv_col
{
    size_t              len;
    t_carr              name;
    struct s_csv_col    *next;
    void                *columns;
}                       t_csv_col;

// -----------------

typedef struct      s_tbnode {
    char            c;
    int             word_index;
    struct s_tbnode *next;
    struct s_tbnode *f_begin;
    struct s_tbnode *f_last;
}                   t_tbnode;

// Prototypes
t_farr          dast_new_farr(size_t len);
t_tbnode        *dast_new_tbnode(char c);
t_carr          dast_new_carr(char *str, size_t len);
t_carr          dast_new_static_carr(char *str, size_t len);
void	        dast_free(void **ap);
t_csv_col       *dast_new_col(int type, size_t len, char *name);
t_csv_float_col *dast_new_csv_float_col(int type, size_t len);
t_csv_str_col   *dast_new_csv_str_col(int type, size_t len);

#endif
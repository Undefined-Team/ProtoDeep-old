#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro

// w = arr, x = type, y = len, z = val
# define arrInit(x, y)          dast_init_arr(x, y)
# define arrNew(x, y, z)        dast_new_arr(x, y, z)
# define arrSNew(x, y, z)       dast_new_s_arr(x, y, z)
# define arrFree(w)             dast_free_arr(w)

# define strNew(z)              arrNew(T_CHAR, 1, z)
# define strSNew(z)             arrSNew(T_CHAR, 1, z)
# define strFree(w)             arrFree(w)

# define t_char_a               t_arr
# define t_float_a              t_arr
# define t_size_t_a             t_arr
# define t_str_a                t_arr

# define PROT_MALLOC(x)         if (!(x)) {return NULL;}
# define PROT_ARR_TYPE(x, y)    if (x != y) {return arrNew(y, 0, NULL);}

# define T_STR                  T_ARR // T_STR is an array of array

// Structures
typedef enum {false,true} bool;
typedef enum {T_ARR, T_FLOAT, T_SIZE_T, T_CHAR} type;

typedef struct      s_arr {
    void            *val;
    size_t          len;
    type            type;
}                   t_arr;

// -----------------

typedef struct          s_csv_col
{
    t_arr                name;
    struct s_csv_col    *next;
    t_arr               columns;
}                       t_csv_col;

typedef struct          s_csv
{
    t_csv_col           *begin;
    size_t              width;
    size_t              height;
}                       t_csv;

// -----------------

typedef struct      s_tbnode {
    char            c;
    int             word_index;
    struct s_tbnode *next;
    struct s_tbnode *f_begin;
    struct s_tbnode *f_last;
}                   t_tbnode;

// Prototypes
t_tbnode        *dast_new_tbnode(char c, int word_index);
void            dast_free_tbnode(t_tbnode *begin);

t_csv_col       *dast_csv_new_col(t_arr columns, t_char_a name);
void            dast_csv_free_col(t_csv_col *elem);

t_arr           dast_init_arr(type type, size_t len);
t_arr           dast_new_s_arr(type type, size_t len, void* val);
t_arr           dast_new_arr(type type, size_t len, void* val);
void            dast_free_arr(t_arr arr);

void	        dast_free(void **ap);

#endif
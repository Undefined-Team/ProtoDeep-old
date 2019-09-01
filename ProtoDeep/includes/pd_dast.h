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
# define PROT_ARR_TYPE(x, y)    if (x != y) {return pd_arrNew(y, 0, NULL);}

# define T_STR                  T_ARR // T_STR is an array of array

// Structures
typedef enum {false,true} bool;
typedef enum {PD_T_ARR, PD_T_FLOAT, PD_T_SIZE_T, PD_T_CHAR} type;

typedef struct      pds_arr {
    void            *val;
    size_t          len;
    type            type;
}                   pd_arr;

// -----------------

typedef struct          pds_csv_col
{
    pd_arr               name;
    struct pds_csv_col    *next;
    pd_arr               columns;
}                       pd_csv_col;

typedef struct          pds_csv
{
    pd_csv_col           *begin;
    size_t              width;
    size_t              height;
}                       pd_csv;

// -----------------

typedef struct      pds_tbnode {
    char            c;
    int             word_index;
    struct pds_tbnode *next;
    struct pds_tbnode *f_begin;
    struct pds_tbnode *f_last;
}                   pd_tbnode;

// Prototypes
pd_tbnode        *pd_dast_new_tbnode(char c, int word_index);
void            pd_dast_free_tbnode(pd_tbnode *begin);

pd_csv_col       *pd_dast_csv_new_col(pd_arr columns, t_char_a name);
void            pd_dast_csv_free_col(t_csv_col *elem);

pd_arr           pd_dast_init_arr(pd_type type, size_t len);
pd_arr           pd_dast_new_s_arr(pd_type type, size_t len, void* val);
pd_arr           pd_dast_new_arr(pd_type type, size_t len, void* val);
void            pd_dast_free_arr(pd_arr arr);

void	        pd_dast_free(void **ap);

#endif
#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
# define PROT_MALLOC(x)         if (!(x)) {return NULL;}

# define arrInit(x, y)        dast_init_arr(x, y)
# define arrNew(x, y, z)      dast_new_arr(x, y, z)
# define arrSNew(x, y, z)     dast_new_s_arr(x, y, z)

# define strNew(x)              arrNew(T_CHAR, 1, x)
# define strSNew(x)             arrSNew(T_CHAR, 1, x)
# define t_str                  t_arr // A CHANGER EN CHAR_A
# define t_float_a              t_arr
# define t_size_t_a             t_arr
# define t_str_a                t_arr

// Structures
typedef enum {false,true} bool;
typedef enum {T_STR, T_FLOAT, T_SIZE_T, T_CHAR} type;

typedef struct      s_arr {
    void            *val;
    size_t          len;
    type            type;
}                   t_arr;

typedef struct      s_varr {
    void           *arr;
    size_t          len;
}                   t_varr;

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

typedef struct          s_csv_col
{
   // size_t              len;
    t_arr                name;
    struct s_csv_col    *next;
    //type                type;
    //void                *columns;
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
t_varr          dast_init_varr(size_t len, size_t so); //A SUPPRIMER
t_farr          dast_new_farr(size_t len); // A SUPPRIMER
t_carr          dast_new_carr(char *str, size_t len); // A SUPPRIMER
t_carr          dast_new_static_carr(char *str, size_t len); // A SUPPRIMER
t_tbnode        *dast_new_tbnode(char c, int word_index);
void	        dast_free(void **ap);
t_csv_col       *dast_csv_new_col(t_arr columns, t_str name);
t_arr           dast_init_arr(type type, size_t len);
t_arr           dast_new_s_arr(type type, size_t len, void* val);
t_arr           dast_new_arr(type type, size_t len, void* val);

#endif
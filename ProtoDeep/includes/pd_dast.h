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

typedef struct      s_tbnode {
    char            c;
    int             word_index;
    struct s_tbnode *next;
    struct s_tbnode *f_begin;
    struct s_tbnode *f_last;
}                   t_tbnode;
// Prototypes
t_farr      dast_new_farr(size_t len);
t_tbnode    *dast_new_tbnode(char c);


#endif
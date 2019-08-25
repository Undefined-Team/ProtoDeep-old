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

typedef struct      s_carr {
    float           *arr;
    size_t          len;
}                   t_carr;

typedef struct      s_tbnode {
    char            c;
    struct s_tbnode *next;
    struct s_tbnode *f_first;
    struct s_tbnode *f_last;
}                   t_tbnode;
// Prototypes
t_farr      dast_new_farr(size_t len);
t_tbnode    *dsat_new_tbnode(char c);


#endif
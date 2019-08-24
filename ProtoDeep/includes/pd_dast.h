#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro

// Structures
typedef enum {false,true} bool;

typedef struct  s_farr {
    float       *arr;
    size_t      len;
}               t_farr;

// Prototypes
t_farr  dast_new_farr(size_t len);


#endif
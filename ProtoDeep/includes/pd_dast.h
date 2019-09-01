#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
// v = depth, w = arr, x = type, y = len, z = val
# define arrInit(x, y)          dast_init_arr(x, y)
# define arrNew(x, y, z)        dast_new_arr(x, y, z)
# define arrSNew(x, y, z)       dast_new_s_arr(x, y, z)
# define arrFree(w)             dast_free_arr(w, 0)
# define arrRFree(w, v)         dast_free_arr(w, v)

# define strNew(z)              arrNew(T_CHAR, 1, z)
# define strSNew(z)             arrSNew(T_CHAR, 1, z)
# define strFree(w)             arrRFree(w, 1)

# define t_char_a               t_arr
# define t_float_a              t_arr
# define t_size_t_a             t_arr
# define t_str_a                t_arr
# define t_stdiz_a              t_arr

# define PROT_MALLOC(x)         if (!(x)) {return NULL;}
# define PROT_ARR_TYPE(x, y)    if (x != y) {return arrNew(y, 0, NULL);}

# define T_STR                  T_ARR // T_STR is an array of array

// Structures
typedef enum {false,true} bool;
typedef enum {T_ARR, T_FLOAT, T_SIZE_T, T_CHAR, T_STDIZ} type;

typedef struct                  s_arr {
    void                        *val;
    size_t                      len;
    type                        type;
}                               t_arr;

// Prototypes
t_arr                           dast_init_arr(type type, size_t len);
t_arr                           dast_new_s_arr(type type, size_t len, void* val);
t_arr                           dast_new_arr(type type, size_t len, void* val);
void                            dast_free_arr(t_arr arr, int depth);

void	                        dast_free(void **ap);

#endif
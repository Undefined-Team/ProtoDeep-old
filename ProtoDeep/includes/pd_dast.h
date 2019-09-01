#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
// v = depth, w = arr, x = type, y = len, z = val
# define pd_arrInit(x, y)           pd_dast_inipd_arr(x, y)
# define pd_arrNew(x, y, z)         pd_dast_new_arr(x, y, z)
# define pd_arrSNew(x, y, z)        pd_dast_new_s_arr(x, y, z)
# define pd_arrFree(w)              pd_dast_free_arr(w, 0)
# define pd_arrRFree(w, v)          pd_dast_free_arr(w, v)

# define pd_strNew(z)               pd_arrNew(PD_T_CHAR, 1, z)
# define pd_strSNew(z)              pd_arrSNew(PD_T_CHAR, 1, z)
# define pd_strFree(w)              pd_arrRFree(w, 1)

# define pd_char_a                  pd_arr
# define pd_float_a                 pd_arr
# define pd_size_t_a                pd_arr
# define pd_str_a                   pd_arr
# define pd_stdiz_a                 pd_arr

# define pd_PROT_MALLOC(x)          if (!(x)) {return NULL;}
# define pd_PROT_ARR_TYPE(x, y)     if (x != y) {return pd_arrNew(y, 0, NULL);}

# define PD_T_STR                   T_ARR // T_STR is an array of array

// Structures
typedef enum {false,true} bool;
typedef enum {PD_T_ARR, PD_T_FLOAT, PD_T_SIZE_T, PD_T_CHAR, PD_T_STDIZ} pd_type;

typedef struct                      pds_arr {
    void                            *val;
    size_t                          len;
    pd_type                         type;
}                                   pd_arr;

// Prototypes
pd_arr                              pd_dast_init_arr(pd_type type, size_t len);
pd_arr                              pd_dast_new_s_arr(pd_type type, size_t len, void* val);
pd_arr                              pd_dast_new_arr(pd_type type, size_t len, void* val);
void                                pd_dast_free_arr(pd_arr arr, int depth);

void	                            pd_dast_free(void **ap);

#endif
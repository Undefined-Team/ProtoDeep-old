#ifndef PD_NTENS_H
# define PD_NTENS_H

// Lib

// Macro

// Structures
typedef struct  pds_ntensor {
    float       *val;
    size_t      len;
    size_t      *shape;
    size_t      *shape_m;
    size_t      shape_len;
}               pd_ntensor;

// Prototypes
pd_ntensor *pd_ntens_init_val(pd_arr *shape, float new_val);
float       pd_ntens_get_val(pd_ntensor *tensor, ...);
float       *pd_ntens_get_pval(pd_ntensor *tensor, ...);

#endif
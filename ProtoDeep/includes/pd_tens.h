#ifndef PD_TENS_H
# define PD_TENS_H

// Lib

// Macro

// Structures
typedef struct  pds_tensor {
    float       *val;
    size_t      len;
    size_t      *shape;
    size_t      *shape_m;
    size_t      *shape_len;
}               pd_tensor;

// Prototypes
pd_tensor *pd_tens_init_val(pd_arr *shape, float new_val);
float       pd_tens_get_val(pd_tens tensor, ...);
float       *pd_tens_get_pval(pd_tens tensor, ...);

#endif
#ifndef PD_TENS_H
# define PD_TENS_H

// Lib

// Macro
# define pd_tens_cpy(x)     pd_tens_init_cpy(x)

// Structures
typedef struct  pds_tensor {
    float       *val;
    size_t      len;
    size_t      *shape;
    size_t      *shape_m;
    size_t      shape_len;
}               pd_tensor;

// Prototypes
pd_tensor   *pd_tens_init(pd_arr *shape);
pd_tensor   *pd_tens_init_val(pd_arr *shape, float new_val);
pd_tensor   *pd_tens_init_rand(pd_arr *shape, float bound_1, float bound_2);
pd_tensor   *pd_tens_init_cpy(pd_tensor *tensor_src);

float       pd_tens_get_mval(pd_tensor *tensor, ...);
float       *pd_tens_get_mpval(pd_tensor *tensor, ...);
float       pd_tens_get_val(pd_tensor *tensor, size_t *coord);
float       *pd_tens_get_pval(pd_tensor *tensor, size_t *coord);

void        pd_tens_print(pd_tensor *tensor);
#endif
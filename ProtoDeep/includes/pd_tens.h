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
size_t     *pd_get_shape_mult(size_t *shape, pd_count shape_len, size_t *len);
pd_tensor   *pd_tens_init(pd_arr *shape);
pd_tensor   *pd_tens_init_val(pd_arr *shape, float new_val);
pd_tensor   *pd_tens_init_rand(pd_arr *shape, float bound_1, float bound_2);
pd_tensor   *pd_tens_init_cpy(pd_tensor *tensor_src);

float       pd_tens_get_mval(pd_tensor *tensor, ...);
float       *pd_tens_get_mpval(pd_tensor *tensor, ...);
float       pd_tens_get_val(pd_tensor *tensor, size_t *coord);
float       *pd_tens_get_pval(pd_tensor *tensor, size_t *coord);

void        pd_tens_print(pd_tensor *tensor);
void        pd_tens_free(pd_tensor *tensor);

pd_tensor   *pd_tens_flatten(pd_tensor *tensor);
pd_tensor   *pd_tens_flatten_copy(pd_tensor *tensor);
pd_tensor   *pd_tens_reshape(pd_tensor *tensor, pd_size_t_a *shape);
pd_tensor   *pd_tens_reshape_copy(pd_tensor *tensor, pd_size_t_a *shape);
pd_tensor   *pd_tens_dot(pd_tensor *a, pd_tensor *b, pd_arr *axis);

#endif
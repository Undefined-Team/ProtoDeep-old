#ifndef PD_TENS_H
# define PD_TENS_H

// Macro

// Structures
typedef struct				pds_tensor {
	void					*val;
	size_t					rank;
	size_t					len;
}							pd_tensor;

// Prototypes
pd_tensor                   pd_tens_init(size_t *shape, size_t len);
pd_size_t_a                 pd_tens_get_shape(pd_tensor tensor);

#endif
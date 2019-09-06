#ifndef PD_TENS_H
# define PD_TENS_H

// Macro
# define pd_tens_print(x)	pd_tens_print_ctr(x, 0)

// Structures
typedef struct				pds_tensor {
	void					*val;
	size_t					rank;
	size_t					len;
	pd_size_t_a             shape;
}							pd_tensor;

// Prototypes
void        				pd_tens_print_ctr(pd_tensor tensor, size_t space);
pd_tensor       			pd_tens_new(size_t rank, size_t len, void *val, pd_arr shape);
pd_tensor   				pd_tens_init(pd_size_t_a shape);
pd_tensor   				pd_tens_init_rand(pd_size_t_a shape, float bound_a, float bound_b);
pd_size_t_a                 pd_tens_get_shape(pd_tensor tensor);
pd_tensor 					pd_tens_copy(pd_tensor tensor);
pd_tensor 					pd_tens_concat(pd_tensor tensor_a, pd_tensor tensor_b, int axis);
void        				pd_tens_free(pd_tensor tensor);
pd_tensor   				pd_tens_flatten(pd_tensor tensor);
pd_tensor   				pd_tens_reshape(pd_tensor tensor, pd_size_t_a shape);
pd_tensor    				pd_tens_dot(pd_tensor a, pd_tensor b, pd_size_t_a axis);
pd_tensor       			pd_tens_transpose(pd_tensor tensor, pd_size_t_a new_dim);
size_t						*pd_tens_shape(size_t len, int dim, ...);

#endif
#ifndef PD_TENS_H
# define PD_TENS_H

// Macro
# define pd_tens_print(x)							pd_tens_print_ctr(x, 0)
//typedef enum {PD_TENS_INIT, PD_TENS_INIT_VAL, PD_TENS_INIT_RAND, PD_TENS_INIT_CPY} pd_tens_init_type;
//# define pd_tens_init(shape)						pd_tens_init_ctr(shape, PD_TENS_INIT, 0, 0)
//# define pd_tens_init_val(shape, value) 			pd_tens_init_ctr(shape, PD_TENS_INIT_VAL, value, 0)
//# define pd_tens_init_rand(shape, bound_1, bound_2) pd_tens_init_ctr(shape, PD_TENS_INIT_RAND, bound_1, bound_2)
//# define pd_tens_copy(tensor)						pd_tens_init_ctr(tensor, PD_TENS_INIT_CPY, 0, 0)
# define pd_tens_cpy(tensor)						pd_tens_init_cpy(tensor)

// Structures
typedef struct				pds_tensor {
	void					*val;
	size_t					rank;
	size_t					len;
	pd_size_t_a             *shape;
}							pd_tensor;

typedef struct          	pds_s_mem_tensor {
    size_t              	shape_len;
    pd_arr              	*new_shapes;
    size_t              	*a_shape;
    size_t              	*shape_div;
    pd_tensor           	*mem_tensor;
    pd_tensor           	**mem_p_tensor;
}                       	pd_s_mem_tensor;

typedef struct          	pds_s_mem_p_tensor {
    size_t              	nbr_p_tensor;
    pd_tensor           	*mem_tensor;
    pd_tensor           	**mem_p_tensor;
}                       	pd_s_mem_p_tensor;

typedef struct          	pds_s_mem_float {
    size_t              	shape_len;
    pd_arr              	*new_shapes;
    size_t              	*a_shape;
    size_t              	*shape_div;
    pd_tensor           	*mem_tensor;
    float               	*mem_float;
}                       	pd_s_mem_float;

// Prototypes
size_t 						*pd_get_shape_div(size_t *a_shape, size_t shape_len, size_t *nbr_float, size_t *nbr_p_tensor, size_t *nbr_tensor);
pd_s_mem_tensor 			pd_get_mem_tensor(size_t shape_len, pd_arr *new_shapes, size_t *a_shape, size_t *shape_div, pd_tensor *mem_tensor, pd_tensor **mem_p_tensor);
pd_s_mem_p_tensor 			pd_get_mem_p_tensor(size_t nbr_p_tensor, pd_tensor *mem_tensor, pd_tensor **mem_p_tensor);
pd_s_mem_float 				pd_get_mem_float(size_t shape_len, pd_arr *new_shapes, size_t *a_shape, size_t *shape_div, pd_tensor *mem_tensor, float *mem_float);
pd_tensor   				*pd_tens_init_ctr(pd_s_mem_tensor s_mem_tensor, pd_s_mem_p_tensor s_mem_p_tensor, pd_s_mem_float s_mem_float);
pd_tensor 					*pd_tens_init(pd_size_t_a *shape);
pd_tensor 					*pd_tens_init_val(pd_size_t_a *shape, float val);
pd_tensor 					*pd_tens_init_rand(pd_size_t_a *shape, float bound_a, float bound_b);
pd_tensor 					*pd_tens_init_cpy(pd_tensor *tens_src);
//void 						pd_tens_init_transpose(pd_tensor *tens_src, pd_size_t_a *new_dim);

// pd_tensor   				*pd_tens_init_new(pd_size_t_a *shape);
// pd_tensor  					*pd_tens_init_ctr(void *shape, pd_tens_init_type init_type, float in_a, float in_b);
// pd_tensor   				*pd_tens_init(pd_size_t_a *shape);
// pd_tensor   				*pd_tens_init_rand(pd_size_t_a *shape, float bound_a, float bound_b);

pd_tensor       			*pd_tens_new(size_t rank, size_t len, void *val, pd_arr *shape);

void        				pd_tens_print_ctr(pd_tensor *tensor, size_t space);
pd_size_t_a                 *pd_tens_get_shape(pd_tensor *tensor);
pd_tensor       			*pd_tens_copy_new(pd_tensor *tensor);
// pd_tensor 					*pd_tens_copy(pd_tensor *tensor);
pd_tensor 					*pd_tens_concat(pd_tensor *tensor_a, pd_tensor *tensor_b, int axis);
void        				pd_tens_free_new(pd_tensor *tensor);
void        				pd_tens_free(pd_tensor *tensor);
pd_tensor       			*pd_tens_transpose(pd_tensor *tensor, pd_size_t_a *new_dim);

pd_tensor   				*pd_tens_flatten(pd_tensor *tensor);
pd_tensor   				*pd_tens_reshape(pd_tensor *tensor, pd_size_t_a *shape);
pd_tensor    				*pd_tens_dot(pd_tensor *a, pd_tensor *b, pd_size_t_a *axis);
pd_size_t_a					pd_tens_shape(size_t len, int dim, ...);
pd_tensor       			*pd_tens_add(pd_tensor *a, pd_tensor *b);

#endif
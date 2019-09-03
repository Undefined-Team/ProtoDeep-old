#ifndef NN_CONFIG_H
# define NN_CONFIG_H

// Macro

// Structures
typedef enum {PD_L_DENSE, PD_L_CONVOLUTION, PD_L_MAXPOOL} pd_layer_type;
typedef enum {PD_A_RELU, PD_A_LRELU, PD_A_SOFTMAX, PD_A_SIGMOID, PD_A_TANH} pd_activation;

typedef struct				pds_tensor {
	void					*val;
	size_t					rank;
	size_t					len;
	pd_size_t_a				shape;
}							pd_tensor;

typedef struct				pds_layer {
	pd_layer_type			layer_type;
	pd_tensor				tensor;
	void					*param;
}							pd_layer;

typedef struct				pds_layer_lst {
	pd_layer				*layer;
	struct pds_layer_lst 	*next;
}							pd_layer_lst;

typedef struct				pds_network {
	pd_layer_lst			*init_layers;
	pd_layer_lst			*lst_end;
	pd_layer				**layers;
	size_t					len;
}							pd_network;

typedef struct				pds_dense_params {
	size_t					neurons;
	pd_activation			activation;
}							pd_dense_params;

typedef struct				pds_conv_params {
	size_t					filters;
	size_t					kernel_size;
	size_t					strides;
	pd_activation			activation;
}							pd_conv_params;

typedef struct				pds_maxpool_params {
	size_t					strides;
	size_t					pool_size[2];
}							pd_maxpool_params;

// Prototypes
pd_tensor					pd_nn_get_output_dense(pd_tensor output, pd_tensor layer);
pd_network					pd_nn_add(pd_network *network, pd_layer *layer);
pd_layer					*pd_nn_dense(size_t nb_neurons, pd_activation activation);
pd_layer					*pd_nn_convolution(size_t filters, size_t kernels, size_t strides, pd_activation activation);
pd_layer					*pd_nn_maxpool(size_t pool_size[2], size_t strides);
bool						pd_nn_is_valid_input(size_t rank, pd_layer_type layer_type);
void						pd_nn_print(pd_network network);
pd_network					pd_nn_init_network(pd_network *network);
void						pd_nn_print(pd_network network);
pd_network					pd_nn_validate(pd_network *network);

#endif

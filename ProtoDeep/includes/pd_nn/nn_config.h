#ifndef NN_CONFIG_H
# define NN_CONFIG_H

// Macro

// Structures
typedef enum {PD_L_DENSE, PD_L_CONVOLUTION, PD_L_MAXPOOL} pd_layer_type;
typedef enum {PD_A_RELU, PD_A_LRELU, PD_A_SOFTMAX, PD_A_SIGMOID, PD_A_TANH} pd_activation;

typedef struct				pds_tensor {
	void					*values;
	size_t					rank;
	size_t					len;
}							pd_tensor;

typedef struct				pds_layer {
	pd_layer_type			layer_type;
	pd_tensor				tensor;
	void					*param;
}							pd_layer;

typedef struct				pds_layer_lst {
	pd_tensor				layer;
	struct pds_layer_list 	*next;
}							pd_layer_lst;

typedef struct				pds_network {
	pd_layer_lst			*init_layers;
	pd_tensor				*layers;
	size_t					len;
}							pd_network;

// Prototypes
pd_tensor					pd_get_output_dense(pd_tensor output, pd_tensor layer);

#endif

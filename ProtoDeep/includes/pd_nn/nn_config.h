#ifndef NN_CONFIG_H
# define NN_CONFIG_H

// Macro

// Structures
typedef enum {L_DENSE, L_CONVOLUTION, L_MAXPOOL} layer_type;
typedef enum {A_RELU, A_LRELU, A_SOFTMAX, A_SIGMOID, A_TANH} activation;

typedef struct		s_tensor
{
	void			*values;
	size_t			rank;
	size_t			len;
}					t_tensor;

typedef struct		s_layer
{
	layer_type		layer_type;
	t_tensor		tensor;
}					t_layer;

typedef struct		s_network
{
	t_tensor		*layers;
	size_t			len;
}					t_network;

// Prototypes
t_tensor			get_output_dense(t_tensor output, t_tensor layer);

#endif

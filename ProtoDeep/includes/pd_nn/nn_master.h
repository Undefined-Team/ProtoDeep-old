#ifndef NN_MASTER_H
# define NN_MASTER_H

// Macro

// Structures
typedef enum {PD_L_DENSE, PD_L_CONVOLUTION, PD_L_MAXPOOL} pd_layer_type;

typedef struct		pds_tensor
{
	void			*values;
	size_t			rank;
	size_t			len;
}					pd_tensor;

typedef struct		pds_layer
{
	pd_layer_type	layer_type;
	pd_tensor		tensor;
}					pd_layer;

typedef struct		pds_network
{
	pd_tensor		*layers;
	size_t			len;
}					pd_network;

// Prototypes
void				pd_nn_master(void *input);
pd_tensor			pd_get_output_dense(pd_tensor output, pd_tensor layer);

#endif

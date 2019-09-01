#include "pd_main.h"

pd_tensor	pd_input_to_tensor(void *input)
{
	pd_tensor	tensor;

	return (tensor);
}

bool		pd_nn_is_valid_input(size_t rank, pd_layer_type layer_type)
{
	if ((layer_type == PD_L_DENSE && rank != 1)
	||	(layer_type == PD_L_CONVOLUTION && !(rank == 2 || rank == 3))
	||	(layer_type == PD_L_POOLING && rank != 2))
		return false;
	return true;
}

size_t		pd_layer_rank(pd_layer_type type)
{
	if (type == PD_L_DENSE)
		return (1);
	else if (type == PD_L_CONVOLUTION || type = PD_L_MAXPOOL)
		return (2);
	return (0);
}

t_layer		*pd_new_layer(pd_layer_type layer_type)
{
	pd_layer		*layer;

	layer = (pd_layer *)malloc(sizeof(pd_layer));
	layer.tensor.rank = pd_layer_rank(pd_layer_type);
	layer.tensor.len = 0;
}

pd_network	*pd_create_network(pd_layer_type layer_type)
{
	pd_network	network;

	network.len = 1;
	network.layers = pd_new_layer(layer_type);
	return (network);
}

pd_network	pd_nn_add(pd_network *network, pd_layer_type layer_type)
{
	if (!network)
		network = *pd_create_network(layer_type);
}

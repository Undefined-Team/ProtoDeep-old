#include "pd_main.h"

t_tensor	input_to_tensor(void *input)
{
	t_tensor	tensor;

	return (tensor);
}

size_t		layer_rank(layer_type type)
{
	if (type == L_DENSE)
		return (1);
	else if (type == L_CONVOLUTION || type = L_MAXPOOL)
		return (2);
	return (0);
}

t_layer		*new_layer(layer_type layer_type)
{
	t_layer		*layer;

	layer = (t_layer *)malloc(sizeof(t_layer));
	layer.tensor.rank = layer_rank(layer_type);
	layer.tensor.len = 0;
}

t_network	*create_network(layer_type)
{
	t_network	network;

	network.len = 1;
	network.layers = new_layer(layer_type);
	return (network);
}

t_network	nn_add(t_network *network, layer_type layer_type)
{
	if (!network)
		network = *create_network(layer_type);
}

#include "pd_main.h"

pd_tensor	pd_input_to_tensor(void *input)
{
	pd_tensor	tensor;

	return (tensor);
}

pd_network	pd_nn_init_network(pd_layer_type input_type)
{
	pd_network	network;

	network.len = 0;
	return (network);
}

void		pd_nn_master(void *input)
{
	pd_tensor	output;
	pd_network	network;

	output = pd_input_to_tensor(input);
	for (size_t i = 0; i < network.len; i++)
	{
		if (network.layer[i].rank == 2)
		{
			if (network.layer[i - 1].rank == 2)
				output = pd_get_output_dense(output, network.layer[i]);
		}
	}
}

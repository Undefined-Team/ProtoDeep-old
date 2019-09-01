#include "pd_main.h"

t_tensor	input_to_tensor(void *input)
{
	t_tensor	tensor;

	return (tensor);
}

t_network	nn_init_network(layer_type input_type)
{
	t_network	network;

	network.len = 0;
	return (network);
}

void		nn_master(void *input)
{
	t_tensor	output;
	t_network	network;

	output = input_to_tensor(input);
	for (size_t i = 0; i < network.len; i++)
	{
		if (network.layer[i].rank == 2)
		{
			if (network.layer[i - 1].rank == 2)
				output = get_output_dense(output, network.layer[i]);
		}
	}
}

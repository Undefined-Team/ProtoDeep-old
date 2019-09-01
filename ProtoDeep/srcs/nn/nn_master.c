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

bool		nn_is_valid_input(size_t rank, layer_type layer_type)
{
	if ((layer_type == L_DENSE && rank != 1)
	||	(layer_type == L_CONVOLUTION && !(rank == 2 || rank == 3))
	||	(layer_type == L_POOLING && rank != 2))
		return false;
	return true;
}

void		nn_master(t_tensor output) 
{
	t_network	network;

	if (!nn_is_valid_input(output.rank - 1, network.layer[0].layer_type)) // Une dimension en moins pour le batch size
	{
		printf("Erreur ma gueule\n");
		exit(0);
	}
	for (size_t i = 0; i < network.len; i++)
	{
		if (network.layer[i].rank == 2)
		{
			if (network.layer[i - 1].rank == 2)
				output = get_output_dense(output, network.layer[i]);
		}
	}
}

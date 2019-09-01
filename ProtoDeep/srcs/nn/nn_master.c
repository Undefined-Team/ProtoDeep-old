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

bool		pd_nn_is_valid_input(size_t rank, pd_layer_type layer_type)
{
	if ((layer_type == PD_L_DENSE && rank != 1)
	||	(layer_type == PD_L_CONVOLUTION && !(rank == 2 || rank == 3))
	||	(layer_type == PD_L_POOLING && rank != 2))
		return false;
	return true;
}

void		pd_nn_master(pd_tensor output) 
{
	pd_network	network;

	if (!pd_nn_is_valid_input(output.rank - 1, network.layer[0].layer_type)) // Une dimension en moins pour le batch size
	{
		printf("Erreur ma gueule\n");
		exit(0);
	}
	for (size_t i = 0; i < network.len; i++)
	{
		if (network.layer[i].rank == 2)
		{
			if (network.layer[i - 1].rank == 2)
				output = pd_get_output_dense(output, network.layer[i]);
		}
	}
}

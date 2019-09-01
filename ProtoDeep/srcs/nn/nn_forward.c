#include "pd_main.h"

void		pd_nn_forward(pd_tensor output) 
{
	pd_network	network;

	if (!pd_nn_is_valid_input(output.rank - 1, network.layer[0].layer_type)) // une dimension en moins pour le batch size
	{
		printf("erreur ma gueule\n");
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

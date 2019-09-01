#include "pd_main.h"

void		nn_forward(t_tensor output)
{
	t_network	network;

	for (size_t i = 1; i < network.len; i++)
	{
		if (network.layer[i].rank == 2)
		{
			if (network.layer[i - 1].rank == 2)
				output = get_output_dense(output, network.layer[i]);
		}
	}
}

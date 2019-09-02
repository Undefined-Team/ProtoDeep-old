#include "pd_main.h"

pd_tensor	pd_nn_get_output(pd_tensor input, pd_layer layer, pd_layer_type before_layer_type)
{
	if (layer.layer_type = PD_L_DENSE)
    {
        if (input.rank == 2) // If before == dense
            return pd_nn_get_output_dense(input, network.layer[i]);
        //else if (input.rank > 2) // If before can be flatten
        //    return pd_nn_get_output_dense(pd_nn_get_output_flatten(input), network.layer[i]);
    }
    // CONVOLUTION POOLING LSTM
}

float	pd_nn_forward(pd_network network, pd_tensor input, pd_tensor target) 
{
	if (!pd_nn_is_valid_input(input.rank, network.layer[0].layer_type))
	{
		printf("erreur ma gueule\n");
		exit(0);
	}
	input = pd_nn_get_output(input, network.layers[0], PD_L_INPUT);
	for (size_t i = 1; i < network.len; i++)
		input = pd_nn_get_output(input, network.layers[i], network.layers[i - 1].layer_type);
	return pd_nn_get_cost(input, target, network.hyperparam.cost_type);
}

void	pd_nn_train_batch(pd_network network, pd_tensor input_batch, pd_tensor target_batch)
{
	float cost = 0;

	for (size_t i = 0; i < input_batch.len; i++)
	{
		cost += pd_nn_forward(network, input_batch[i], target_batch[i])
	}
	pd_nn_backward(network, pd_nn_get_first_gradient(cost));
}
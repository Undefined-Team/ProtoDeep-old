#include "pd_main.h"

pd_tensor	pd_nn_input_to_tensor(void *input)
{
	pd_tensor	tensor;

	return (tensor);
}

bool		pd_nn_is_valid_input(size_t rank, pd_layer_type layer_type)
{
	if ((layer_type == PD_L_DENSE && rank != 1)
	||	(layer_type == PD_L_CONVOLUTION && !(rank == 2 || rank == 3))
	||	(layer_type == PD_L_MAXPOOL && rank != 2))
		return false;
	return true;
}

size_t		pd_nn_layer_rank(pd_layer_type type)
{
	if (type == PD_L_DENSE)
		return (1);
	else if (type == PD_L_CONVOLUTION || type == PD_L_MAXPOOL)
		return (2);
	return (0);
}

pd_layer_lst	*pd_nn_add_layer(pd_layer *layer)
{
	pd_layer_lst	*elem;

	elem = (pd_layer_lst *)malloc(sizeof(pd_layer_lst));
	elem->layer = layer;
	elem->next = NULL;
	return (elem);
}

pd_layer	*pd_nn_dense(size_t nb_neurons, pd_activation activation)
{
	pd_layer		*layer;
	pd_dense_params	*params;

	layer = (pd_layer *)malloc(sizeof(pd_layer));
	params = (pd_dense_params *)malloc(sizeof(pd_dense_params));
	layer->layer_type = PD_L_DENSE;
	params->neurons = nb_neurons;
	params->activation = activation;
	layer->param = params;
	return (layer);
}

pd_layer	*pd_nn_convolution(size_t filters, size_t kernels, size_t strides, pd_activation activation)
{
	pd_layer		*layer;
	pd_conv_params	*params;

	layer = (pd_layer *)malloc(sizeof(pd_layer));
	params = (pd_conv_params *)malloc(sizeof(pd_conv_params));
	layer->layer_type = PD_L_CONVOLUTION;
	params->filters = filters;
	params->kernel_size = kernels;
	params->strides = strides;
	params->activation = activation;
	layer->param = params;
	return (layer);
}

pd_layer	*pd_nn_maxpool(size_t pool_size[2], size_t strides)
{
	pd_layer			*layer;
	pd_maxpool_params	*params;

	layer = (pd_layer *)malloc(sizeof(pd_layer));
	params = (pd_maxpool_params *)malloc(sizeof(pd_maxpool_params));
	layer->layer_type = PD_L_MAXPOOL;
	params->pool_size[0] = pool_size[0];
	params->pool_size[1] = pool_size[1];
	params->strides = strides;
	layer->param = params;
	return (layer);
}

pd_network	pd_nn_add(pd_network *network, pd_layer *layer)
{
	if (!network->init_layers)
	{
		network->init_layers = pd_nn_add_layer(layer);
		network->lst_end = network->init_layers;
	}
	else
	{
		network->lst_end->next = pd_nn_add_layer(layer);
		network->lst_end = network->lst_end->next;
	}
	network->len++;
	return (*network);
}

pd_network	pd_nn_init_network(pd_network *network)
{
	network->len = 0;
	network->init_layers = NULL;
	network->lst_end = NULL;
	return (*network);
}

pd_network	pd_nn_validate(pd_network *network)
{
	network->layers = (pd_layer **)malloc(network->len * sizeof(pd_layer *));
	network->lst_end = network->init_layers;
	for (size_t i = 0; i < network->len; i++)
	{
		network->layers[i] = network->lst_end->layer;
		network->lst_end = network->lst_end->next;
	}
	return (*network);
}
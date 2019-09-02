#include "pd_main.h"

char	*pd_nn_get_activation(pd_activation activation)
{
	if (activation == PD_A_RELU)
		return("Relu");
	else if (activation == PD_A_LRELU)
		return("Lrelu");
	else if (activation == PD_A_SOFTMAX)
		return("Softmax");
	else if (activation == PD_A_SIGMOID)
		return ("Sigmoid");
	else if (activation == PD_A_TANH)
		return ("tanh");
	return (NULL);
}

void		pd_nn_print_dense(pd_layer *layer)
{
	pd_dense_params *param = (pd_dense_params *)layer->param;

	printf(">> %s%sDense Layer%s%s:\n", PD_COLOR_U, PD_COLOR_1, PD_COLOR_N, PD_COLOR_1);
	printf("Number of neurons:    %zd\n", param->neurons);
	printf("Activation:         %s\n\n", pd_nn_get_activation(param->activation));
    printf("%s", PD_COLOR_N);
}

void		pd_nn_print_convolution(pd_layer *layer)
{
	pd_conv_params *param = (pd_conv_params *)layer->param;

	printf(">> %s%sConvolution Layer%s%s:\n", PD_COLOR_U, PD_COLOR_2, PD_COLOR_N, PD_COLOR_2);
	printf("Number of filters:  %zd\n", param->filters);
	printf("Kernel size:        %zd\n", param->kernel_size);
	printf("Strides size:       %zd\n", param->strides);
	printf("Activation:         %s\n\n", pd_nn_get_activation(param->activation));
    printf("%s", PD_COLOR_N);
}

void		pd_nn_print_maxpool(pd_layer *layer)
{
	pd_maxpool_params *param = (pd_maxpool_params *)layer->param;

	printf(">> %s%sMaxpool Layer%s%s:\n", PD_COLOR_U, PD_COLOR_3, PD_COLOR_N, PD_COLOR_3);
	printf("Pool size:          (%zd, %zd)\n", param->pool_size[0], param->pool_size[1]);
	printf("Strides size:       %zd\n\n", param->strides);
    printf("%s", PD_COLOR_N);
}

void		pd_nn_print(pd_network network)
{
	for (size_t i = 0; i < network.len; i++)
	{
		pd_layer *layer = network.layers[i];
		if (layer->layer_type == PD_L_DENSE)
			pd_nn_print_dense(layer);
		else if (layer->layer_type == PD_L_CONVOLUTION)
			pd_nn_print_convolution(layer);
		else if (layer->layer_type == PD_L_MAXPOOL)
			pd_nn_print_maxpool(layer);
	}
}
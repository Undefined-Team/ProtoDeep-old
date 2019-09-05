#include "pd_main.h"

/*
pd_tensor	pd_nn_get_output_dense(pd_tensor input, pd_tensor layer)
{
	// pd_tensor output;

	output.len = input.tensor.len;
	output.val = pd_malloc(output.len * sizeof(float));
	for (size_t i = 0; i < output.len; i++)
		((float *)output.val)[i] = 0;
	if (input.rank != 1)
		printf("Error\n");
	for (size_t i = 0; i < layer.tensor.len; i++)
	{
		pd_tensor tensor = ((pd_tensor *)layer.tensor.val)[i];
		float sum = 0;
		for (size_t j = 0; j < tensor.len; j++)
		{
			sum += ((float *)tensor.val)[j];
		}
		((float *)output.val)[i] = sum * ((float *)input.val)[i];
	}
	return (output);
}
*/

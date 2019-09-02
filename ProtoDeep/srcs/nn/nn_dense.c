#include "pd_main.h"

pd_tensor	pd_nn_get_output_dense(pd_tensor output, pd_tensor layer)
{
	if (output.rank == layer.rank)
		return (output);
	return (output);
}

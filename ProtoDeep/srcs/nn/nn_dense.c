#include "pd_main.h"

t_tensor	get_output_dense(t_tensor output, t_tensor layer)
{
	if (output.rank == layer.rank)
		return (output);
	return (output);
}

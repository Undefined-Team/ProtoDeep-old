#include "pd_main.h"

void	pd_free_ctr(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}
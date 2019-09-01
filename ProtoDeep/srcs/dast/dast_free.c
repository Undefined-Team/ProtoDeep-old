#include "pd_main.h"

void	pd_dast_free(void **ap)
{
	free(*ap);
	*ap = NULL;
}

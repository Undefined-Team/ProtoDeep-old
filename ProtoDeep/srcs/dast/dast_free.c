#include "pd_main.h"

void	dast_free(void **ap)
{
	free(*ap);
	*ap = NULL;
}

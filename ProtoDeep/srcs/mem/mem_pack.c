#include "pd_main.h"

void        pd_mem_cpy(void* dst, void *src, size_t len)
{
	while (len-- > 0) *(char*)dst++ = *(char*)src++;
}

void        pd_mem_set(void *dst, int c, size_t len)
{
  unsigned char *ptr = dst;
  while (len-- > 0) *ptr++ = c;
}
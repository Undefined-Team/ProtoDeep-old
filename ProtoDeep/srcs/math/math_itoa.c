#include "pd_main.h"

static pd_char_a pd_get_number(int n, int div, int neg, int size)
{
	pd_char_a    nb;
	int		    i;

	i = 0;
	if (neg == -1)
		size++;
    nb = pd_arr_init(PD_T_CHAR, size + 2);
	if (neg == -1)
		((char *)nb.val)[i++] = '-';
	while (div > 0)
	{
		((char *)nb.val)[i++] = n / div + '0';
		n %= div;
		div /= 10;
	}
	((char *)nb.val)[i] = '\0';
	return (nb);
}

static pd_char_a pd_return_int_min(void)
{
	pd_char_a    min;

	min = pd_str_new_s("-2147483648");
	return (min);
}

pd_char_a    pd_math_itoa(int n)
{
	int		neg;
	int		div;
	int		size;

	size = 0;
	div = 1;
	neg = 1;
	if (n == -2147483648)
		return (pd_return_int_min());
	if (n < 0)
	{
		neg = -1;
		n *= -1;
	}
	while (n / div > 9)
	{
		size++;
		div *= 10;
	}
	return (pd_get_number(n, div, neg, size));
}
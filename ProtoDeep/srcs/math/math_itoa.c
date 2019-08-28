#include "pd_main.h"

static t_char_a ft_getnumber(int n, int div, int neg, int size)
{
	t_char_a    nb;
	int		    i;

	i = 0;
	if (neg == -1)
		size++;
    nb = arrInit(T_CHAR, size + 2);
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

static t_char_a ft_returnintmin(void)
{
	t_char_a    min;

	min = strSNew("-2147483648");
	return (min);
}

t_char_a    math_itoa(int n)
{
	int		neg;
	int		div;
	int		size;

	size = 0;
	div = 1;
	neg = 1;
	if (n == -2147483648)
		return (ft_returnintmin());
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
	return (ft_getnumber(n, div, neg, size));
}
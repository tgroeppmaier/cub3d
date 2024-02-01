#include "cub3D.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

static void	output(int n)
{
	if (n > 9)
		output(n / 10);
	n = n % 10 + '0';
	write(1, &n, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0 && n != -2147483648)
	{
		write(1, "-", 1);
		n *= -1;
	}
	output(n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	if (n == 0)
		return (s);
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

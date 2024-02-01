#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		++p;
	return (p - s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size != 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}

int	ft_wcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		k;
	int		count;

	k = 0;
	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (ft_wcount(s, c) + 1));
	if (!array)
		return (NULL);
	while (*s)
	{
		count = 0;
		while (*s != c && *s)
		{
			count++;
			s++;
		}
		if (count > 0)
			array[k++] = ft_strndup(s - count, count);
		if (*s)
			s++;
	}
	array[k] = NULL;
	return (array);
}

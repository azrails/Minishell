
#include "libft.h"

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char		*a;
	unsigned char		*b;
	size_t				i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while ((a[i] || b[i]) && (i < n))
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}


#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *a;

	a = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*a == (unsigned char)c)
			return (a);
		a++;
	}
	return (NULL);
}

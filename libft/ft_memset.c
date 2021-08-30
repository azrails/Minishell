
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *a;

	a = (unsigned char *)s;
	while (n--)
		*a++ = (unsigned char)c;
	return (s);
}
